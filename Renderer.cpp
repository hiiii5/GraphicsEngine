#include "Renderer.h"

#include <cstring>

#include "MathDefines.h"
#include "MathHelper.h"
#include "Camera.h"
#include "Vector2.h"
#include "Vector3.h"

// TODO Initialize current vertex program or remove.
Renderer::Renderer(const uint32_t Width, const uint32_t Height, const uint32_t ClearColor): Width(Width),
																							Height(Height),
																							ClearColor(ClearColor) {
	const auto size = GetScreenSize() * sizeof Pixels;
	Pixels = new uint32_t[size];

	for (uint32_t i = 0; i < size; i++) { Pixels[i] = ClearColor; }

	// Setup initial old pixel to match clear Color for screen.
	OldPixels = new uint32_t[size];
	memcpy(OldPixels, Pixels, size);
}

Renderer::~Renderer() { delete[] Pixels; delete[] OldPixels; /*delete CurrentVertexProgram;*/ }

void Renderer::ClearBuffer() const {
	for (uint32_t i = 0; i < GetScreenSize() * sizeof Pixels; i++) { Pixels[i] = ClearColor; }
}

void Renderer::DrawPixel(const uint32_t& Pixel, const uint32_t X, const uint32_t Y) const {
	if (X >= Width || Y >= Height) return;

	// BlEnd the old pixel with the new pixel.
	const unsigned short foregroundAlpha = ((Pixel & 0xFF000000) >> 24) / 255;

	auto& target = Pixels[Y * Width + X];

	if (foregroundAlpha <= 0) {
		target ^= ClearColor;
		return;
	}

	const uint32_t foregroundRed = (Pixel & 0x00FF0000) >> 16;
	const uint32_t foregroundGreen = (Pixel & 0x0000FF00) >> 8;
	const uint32_t foregroundBlue = (Pixel & 0x000000FF);

	// Get the old pixels rgb values and average the alphas.
	const uint32_t backgroundRed = (target & 0x00FF0000) >> 16;
	const uint32_t backgroundGreen = (target & 0x0000FF00) >> 8;
	const uint32_t backgroundBlue = (target & 0x000000FF);

	const auto outputRed = (foregroundRed * foregroundAlpha) + (backgroundRed * (1.0 - foregroundAlpha));
	const auto outputGreen = (foregroundGreen * foregroundAlpha) + (backgroundGreen * (1.0 - foregroundAlpha));
	const auto outputBlue = (foregroundBlue * foregroundAlpha) + (backgroundBlue * (1.0 - foregroundAlpha));

	const uint32_t red = MathHelper::Floor(outputRed) << 16;
	const uint32_t green = MathHelper::Floor(outputGreen) << 8;
	const uint32_t blue = MathHelper::Floor(outputBlue);

	target = foregroundAlpha << 24 | red | green | blue;

}

void Renderer::DrawLine(const Vector2& Start, const Vector2& End, const uint32_t Color) const {
	Vector2 lp, rp;

	// Make sure Ax < Bx if not then swap A with B. Eliminating the left octants of the screen.
	if(End.GetX() > Start.GetX()) {
		rp = End;
		lp = Start;
	}
	else {
		rp = Start;
		lp = End;
	}

	// Check to see if |Dx| > |Dy| (top and bottom quadrant) or if |Dy| > |Dx| (middle two quadrants)
	// int Dx = Bx - Ax
	int deltaX = static_cast<int>(rp.GetX() - lp.GetX());
	// int Dy = abs(By - Ay)
	int deltaY = static_cast<int>(std::abs(rp.GetY() - lp.GetY()));

	int i;
	float ndx, ndy;
	float x, y;

	// If the change in x is greater than the change in y, then we are in the middle two octants.
	if(deltaX > deltaY) {
		// Get the signed value of delta y
		deltaY = rp.GetY() - lp.GetY(); // Truncate the float.
		ndy = 1.0*deltaY / deltaX;

		x = lp.GetX();
		y = lp.GetY();

		for (i = 0; i < deltaX; i++) {
			DrawPixel(Color, x, y);
			x++;
			y += ndy;
		}
	}
	else { // the change in y is greater than the change in x so we are in one of the two outer octants.
		deltaY = rp.GetY() - lp.GetY();

		ndx = 1.0*deltaX / std::abs(deltaY);
		x = lp.GetX();
		y = lp.GetY();

		for (i = 0; i < std::abs(deltaY); i++) {
			DrawPixel(Color, x, y);
			y += rp.GetY() < lp.GetY() ? -1 : 1;
			x += ndx;
		}
	}
}

void Renderer::DrawGrid(const Camera* Viewer, const int WidthDivisions, const int HeightDivisions, const float GridWidth, const float GridHeight, const uint32_t& Color) const {
	// Draw x lines
	const auto halfWidth = (GridWidth / 2);
	const auto halfHeight = (GridWidth / 2);

	float j;
	// Draw x lines
	const auto deltaX = (GridWidth / WidthDivisions) * 2;
	for (j = -GridHeight; j <= GridHeight; j += deltaX) {
		const auto a = Vector3{j, 0, -GridWidth };
		const auto b = Vector3{j, 0, GridWidth};
		DrawLine(Viewer->ProjectOntoScreen2(a), Viewer->ProjectOntoScreen2(b), Color);
	}

	// Draw y lines
	const auto deltaY = (GridHeight / HeightDivisions) * 2;
	for (j = -GridHeight; j <= GridHeight; j += deltaY) {
		const auto a = Vector3{-GridWidth, 0, j};
		const auto b = Vector3{GridWidth, 0, j};
		DrawLine(Viewer->ProjectOntoScreen2(a), Viewer->ProjectOntoScreen2(b), Color);
	}
}

void Renderer::DrawUnitAxis(const Camera* C, const float AxisLength) const {
	const auto x2 = Vector3::XVector3() * AxisLength;
	const auto y2 = Vector3::YVector3() * AxisLength;
	const auto z2 = Vector3::ZVector3() * AxisLength;

	DrawLine(C->ProjectOntoScreen2(Vector3::ZeroVector3()), C->ProjectOntoScreen2(x2), 0xFFAA0000);
	DrawLine(C->ProjectOntoScreen2(Vector3::ZeroVector3()), C->ProjectOntoScreen2(y2), 0xFF00AA00);
	DrawLine(C->ProjectOntoScreen2(Vector3::ZeroVector3()), C->ProjectOntoScreen2(z2), 0xFF0000AA);
}

void Renderer::DrawWireCube(const Camera* C, const Matrix4X4& Transform, const float Scale,const uint32_t& Color) const {

	Vector3 points[8];

	const auto halfScale = Scale / 2;

	// Create a box from left to right so 2x scale.
	points[0] = Vector3(-halfScale, -halfScale, -halfScale);
	points[1] = Vector3( halfScale, -halfScale, -halfScale);
	points[2] = Vector3( halfScale,  halfScale, -halfScale);
	points[3] = Vector3(-halfScale,  halfScale, -halfScale);
	points[4] = Vector3(-halfScale, -halfScale,  halfScale);
	points[5] = Vector3( halfScale, -halfScale,  halfScale);
	points[6] = Vector3( halfScale,  halfScale,  halfScale);
	points[7] = Vector3(-halfScale,  halfScale,  halfScale);

	// TODO Fix
	/*if(CurrentVertexProgram) {
		for (int i = 0; i < 8; ++i) {
			points[i] = CurrentVertexProgram->BindAndExecute([](){}, Vertex{ points[i] });
		}
	}*/

	Vector2 projectedPoints[8];
	for (int i = 0; i < 8; ++i) {
		projectedPoints[i] = C->ProjectOntoScreen2(points[i], Transform);
	}

	for (int i = 0; i < 4; ++i) {
		DrawLine(projectedPoints[i], projectedPoints[(i + 1) % 4], Color);
		DrawLine(projectedPoints[i + 4], projectedPoints[((i + 1) % 4) + 4], Color);
		DrawLine(projectedPoints[i], projectedPoints[i + 4], Color);
	}
}

//void Renderer::SetVertexShader(const VertexShader& NewVertexShader) {
//	// TODO Fix
//	//CurrentVertexProgram = NewVertexShader;
//}

void Renderer::UpdateFrame() const { memcpy(OldPixels, Pixels, GetScreenSize() * sizeof Pixels); }

uint32_t* Renderer::GetFrame() const { return OldPixels; }
