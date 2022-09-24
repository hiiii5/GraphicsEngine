#include "RenderHelper.h"

#include "GEngine.h"
#include "EngineDefines.h"
#include "Shader.h"
#include "tiles_12.h"

void RenderHelper::VertexShader(Vert& V, Mat4& T, const Camera& C) {
	if (CurrentShader) {
		CurrentShader->VertexShader(V, T, C);
	}
}

void RenderHelper::DrawDepth(const std::vector<float>& DepthBuffer) {
	for (int y = 0; y < GEngine::Get()->Width; ++y) {
		for (int x = 0; x < GEngine::Get()->Height; ++x) {
			auto curDepth = DepthBuffer[TwoD2OneD(x, y, GEngine::Get()->Width)];
			DrawPixel(Color(255.0f, curDepth, curDepth, curDepth).Get(), x, y);
		}
	}
}

void RenderHelper::DrawPixel(const unsigned& Pixel, const unsigned X, const unsigned Y) {
	const auto engine = GEngine::Get();

	// Do not draw pixels off screen.
	if (X >= engine->Width || Y >= engine->Height) return;

	auto foreground = Color(Pixel);
	auto& target = engine->Pixels[TwoD2OneD(X, Y, GEngine::Get()->Width)];
	const auto background = Color(target);

	if (foreground.A <= 0) {
		target ^= 0xFF000000;
		return;
	}

	const auto result = Color::AlphaBlend(foreground, background);

	target = result.Get();
}

void RenderHelper::DrawLine(const Vec2F& Start, const Vec2F& End) {
	Vec2F lp, rp;

	// Make sure Ax < Bx if not then swap A with B. Eliminating the left octants of the screen.
	if (End.X > Start.X) {
		rp = End;
		lp = Start;
	}
	else {
		rp = Start;
		lp = End;
	}

	// Check to see if |Dx| > |Dy| (top and bottom quadrant) or if |Dy| > |Dx| (middle two quadrants)
	// int Dx = Bx - Ax
	const int deltaX = static_cast<int>(rp.X - lp.X);
	// int Dy = abs(By - Ay)
	int deltaY = static_cast<int>(std::abs(rp.Y - lp.Y));

	int i;
	float x, y;

	// If the change in x is greater than the change in y, then we are in the middle two octants.
	if (deltaX > deltaY) {
		// Get the signed value of delta y
		deltaY = static_cast<int>(rp.Y - lp.Y); // Truncate the float.
		const float ndy = static_cast<float>(deltaY) / static_cast<float>(deltaX);

		x = lp.X;
		y = lp.Y;

		for (i = 0; i < deltaX; i++) {
			Color c = Color(Color::White);
			Vec2F uv = { 0,0 };
			if (CurrentShader) { CurrentShader->PixelShader(c, uv); }

			DrawPixel(c.Get(), static_cast<uint32_t>(x), static_cast<uint32_t>(y)); // Truncate the float
			x++;
			y += ndy;
		}
	}
	else {
		// the change in y is greater than the change in x so we are in one of the two outer octants.
		deltaY = static_cast<int>(rp.Y - lp.Y);

		const float ndx = static_cast<float>(deltaX) / static_cast<float>(std::abs(deltaY));
		x = lp.X;
		y = lp.Y;

		for (i = 0; i < std::abs(deltaY); i++) {
			Color c = Color(Color::White);
			Vec2F uv = { 0,0 };
			if (CurrentShader) { CurrentShader->PixelShader(c, uv); }

			DrawPixel(c.Get(), static_cast<uint32_t>(x), static_cast<uint32_t>(y)); // Truncate the float
			y += rp.Y < lp.Y ? -1 : 1;
			x += ndx;
		}
	}
}

void RenderHelper::DrawWireCube(const Camera* C, Mat4& Transform, const float Scale, Shader RenderShader) {
	const auto halfScale = Scale / 2;

	Vec3F points[8];
	// Create a box from left to right so 2x scale.
	points[0] = Vec3F(-halfScale, -halfScale, -halfScale);
	points[1] = Vec3F(halfScale, -halfScale, -halfScale);
	points[2] = Vec3F(halfScale, halfScale, -halfScale);
	points[3] = Vec3F(-halfScale, halfScale, -halfScale);
	points[4] = Vec3F(-halfScale, -halfScale, halfScale);
	points[5] = Vec3F(halfScale, -halfScale, halfScale);
	points[6] = Vec3F(halfScale, halfScale, halfScale);
	points[7] = Vec3F(-halfScale, halfScale, halfScale);

	Vec2F projectedPoints[8]{};
	for (int i = 0; i < 8; ++i) {
		float depth;
		projectedPoints[i] = Camera::WorldToScreen(*C, {points[i] , Color()}, Transform);
	}

	CurrentShader = &RenderShader;
	
	for (int i = 0; i < 4; ++i) {
		DrawLine(projectedPoints[i], projectedPoints[(i + 1) % 4]);
		DrawLine(projectedPoints[i + 4], projectedPoints[((i + 1) % 4) + 4]);
		DrawLine(projectedPoints[i], projectedPoints[i + 4]);
	}

	CurrentShader = nullptr;
}

void RenderHelper::DrawWireTriangle(const Camera* C, Mat4& Transform, const std::vector<Vert>& Vertices) {
	DrawLine(Camera::WorldToScreen(*C, Vertices[0], Transform), Camera::WorldToScreen(*C, Vertices[1], Transform));
	DrawLine(Camera::WorldToScreen(*C, Vertices[1], Transform), Camera::WorldToScreen(*C, Vertices[2], Transform));
	DrawLine(Camera::WorldToScreen(*C, Vertices[2], Transform), Camera::WorldToScreen(*C, Vertices[0], Transform));
}

void RenderHelper::DrawWireMesh(const Camera* C, Mat4& Transform, std::vector<Vert> Vertices,
								const std::vector<unsigned>& Indices) {
	for (uint32_t i = 0; i < Indices.size(); i += 3) {
		std::vector<Vert> curTriangle;
		curTriangle.emplace_back(Vertices[Indices[i]]);
		curTriangle.emplace_back(Vertices[Indices[i + 1]]);
		curTriangle.emplace_back(Vertices[Indices[i + 2]]);
		DrawWireTriangle(C, Transform, curTriangle);
	}
}

void RenderHelper::DrawGrid(const Camera* Viewer, int WidthDivisions, int HeightDivisions, float GridWidth,
							float GridHeight, const uint32_t& Color) {
	// Draw x lines
	const auto halfWidth = (GridWidth / 2);
	const auto halfHeight = (GridWidth / 2);

	float j;
	// Draw x lines
	Mat4 trans = {};
	const auto deltaX = (GridWidth / WidthDivisions) * 2;
	for (j = -GridHeight; j <= GridHeight; j += deltaX) {
		const auto a = Vec3F{j, 0, -GridWidth};
		const auto b = Vec3F{j, 0, GridWidth};

		DrawLine(Camera::WorldToScreen(*Viewer, {a, {}}, trans), Camera::WorldToScreen(*Viewer, {b, {}}, trans));
	}

	// Draw y lines
	const auto deltaY = (GridHeight / HeightDivisions) * 2;
	for (j = -GridHeight; j <= GridHeight; j += deltaY) {
		const auto a = Vec3F{-GridWidth, 0, j};
		const auto b = Vec3F{GridWidth, 0, j};
		DrawLine(Camera::WorldToScreen(*Viewer, {a, {}}, trans), Camera::WorldToScreen(*Viewer, {b, {}}, trans));
	}
}

void RenderHelper::FillTriangle(const Camera* C, Mat4& Transform, const std::vector<Vert>& Vertices, const std::vector<Vec2F>& Uv) {
	// Copy the vertices.
	Vert p1, p2, p3;
	p1 = Vertices[0];
	p2 = Vertices[1];
	p3 = Vertices[2];

	// Run vertex shader on the copies.
	RenderHelper::VertexShader(p1, Transform, *C);
	RenderHelper::VertexShader(p2, Transform, *C);
	RenderHelper::VertexShader(p3, Transform, *C);

	// Convert the 3 vertices of the triangle to screen space.
	auto v0 = Camera::WorldToScreen(*C, p1, Transform);
	auto v1 = Camera::WorldToScreen(*C, p2, Transform);
	auto v2 = Camera::WorldToScreen(*C, p3, Transform);

	// CA: BACKFACE CULLING
	float fWinding  = ImplicitLineEquation(v0, v1, v2);
	if (fWinding < 0.0f)
		return;

	auto invV0 = 1 / v0.Z;
	auto invV1 = 1 / v1.Z;
	auto invV2 = 1 / v2.Z;

	auto scaledUv0 = Uv[0] / v0.Z;
	auto scaledUv1 = Uv[1] / v1.Z;
	auto scaledUv2 = Uv[2] / v2.Z;

	// Get the bounding box for the triangle
	auto maxX = Floor(Max(v0.X, Max(v1.X, v2.X)));
	auto minX = Floor(Min(v0.X, Min(v1.X, v2.X)));
	auto maxY = Floor(Max(v0.Y, Max(v1.Y, v2.Y)));
	auto minY = Floor(Min(v0.Y, Min(v1.Y, v2.Y)));
	
	minX = max(minX, 0);
	minY = max(minY, 0);
	maxX = min(maxX, GEngine::Get()->Width - 1);
	maxY = min(maxY, GEngine::Get()->Height - 1);

	// Calculate the area of the parallelogram.
	//const auto area = Edge(v2, v1, v0);

	// For every point in the bounding box, determine if it falls on the triangle.
	for (unsigned y = minY; y <= maxY; y++) {
		for (unsigned x = minX; x <= maxX; x++) {
			const auto p = Vec2F{ (float)x, (float)y };

			const auto bary = GetBarycentric(p, v0, v1, v2);

			if (bary.X < 0.0f || bary.X > 1.0f || bary.Y < 0.0f || bary.Y > 1.0f || bary.Z < 0.0f || bary.Z > 1.0f)
				continue;

			// Interpolate between the depth of the original points.
			const auto lerpZ = v0.Z * bary.X + v1.Z * bary.Y + v2.Z * bary.Z;

			const auto engine = GEngine::Get();

			// Check the depth of the current pixel and if it is farther away than the older one.
			if(engine->Depth[TwoD2OneD(x, y, engine->Width)] <= lerpZ || lerpZ < C->NearPlane || lerpZ > C->FarPlane) continue;

			// Calculate perspective correct uv coordinate.
			const auto invW = invV0 * bary.X + invV1 * bary.Y + invV2 * bary.Z;

			Vec2F uv = scaledUv0 * bary.X + scaledUv1 * bary.Y + scaledUv2 * bary.Z;
			uv /= invW;
			
			// Calculate the average color for the current point.
			const float a = bary.X * p1.C.A + bary.Y * p2.C.A + bary.Z * p3.C.A;
			const float r = bary.X * p1.C.R + bary.Y * p2.C.G + bary.Z * p3.C.B;
			const float g = bary.X * p1.C.R + bary.Y * p2.C.G + bary.Z * p3.C.B;
			const float b = bary.X * p1.C.R + bary.Y * p2.C.G + bary.Z * p3.C.B;

			// Calculate interpolated lighting value.
			const float lr = bary.X * p1.Light.X + bary.Y * p2.Light.X + bary.Z * p3.Light.X;
			const float lg = bary.X * p1.Light.Y + bary.Y * p2.Light.Y + bary.Z * p3.Light.Y;
			const float lb = bary.X * p1.Light.Z + bary.Y * p2.Light.Z + bary.Z * p3.Light.Z;

			// Run the current pixel shader to affect the final color and uv.
			Color col{a, r, g, b};
			if (CurrentShader) {
				CurrentShader->PixelShader(col, uv);
			}

			// Apply lighting.
			col.R *= lr;
			col.G *= lg;
			col.B *= lb;

			// Update the depth of this pixel in the buffer.
			engine->Depth[TwoD2OneD(x, y, engine->Width)] = lerpZ;

			DrawPixel(col.Get(), x, y);
		}
	}
}

void RenderHelper::FillMesh(const Camera* C, Mat4& Transform, std::vector<Vert> Vertices,
							const std::vector<unsigned>& Indices, const std::vector<Vec2F>& Uv) {
	for (uint32_t i = 0; i < Indices.size(); i += 3) {
		std::vector<Vert> curTriangle;
		curTriangle.emplace_back(Vertices[Indices[i]]);
		curTriangle.emplace_back(Vertices[Indices[i + 1]]);
		curTriangle.emplace_back(Vertices[Indices[i + 2]]);

		std::vector<Vec2F> curUv;
		curUv.emplace_back(Uv[i]);
		curUv.emplace_back(Uv[i + 1]);
		curUv.emplace_back(Uv[i + 2]);

		FillTriangle(C, Transform, curTriangle, curUv);
	}
}

void RenderHelper::ClearBuffer() {
	const auto engine = GEngine::Get();

	engine->Depth.assign(engine->Pixels.size(), 1000000.0f);
	engine->Pixels.assign(engine->Pixels.size(), 0xFF13294B);
}

