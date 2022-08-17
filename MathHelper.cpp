#include "MathHelper.h"

#include "Vector2.h"
#include "MathDefines.h"

Vector2 MathHelper::GetParallelVec(const Vector2& A, const Vector2& B) {
	return {B.GetX() - A.GetX(), B.GetY() - A.GetY()};
}

Vector2 MathHelper::GetGradientVec(const Vector2& A, const Vector2& B) {
	return {A.GetY() - B.GetY(), B.GetX() - A.GetX()};
}

double MathHelper::LerpD(const double& A, const double& B, const float Ratio) {
	return (B - A) * static_cast<double>(Ratio) + A;
}

float MathHelper::LerpF(const double& A, const double& B, const float Ratio) {
	return static_cast<float>((B - A) * static_cast<double>(Ratio) + A);
}

uint32_t MathHelper::Floor(const double A) { return static_cast<uint32_t>(A); }

double MathHelper::SolveLine(const double& CurX, const Vector2& P1, const Vector2& P2) {
	const double a = P1.GetY() - P2.GetY();
	const double b = P2.GetX() - P1.GetX();
	const double c = (P1.GetX() - P2.GetX()) * P1.GetY() + (P2.GetY() - P1.GetY()) * P1.GetX();

	return (a * CurX + c) / b;
}

double MathHelper::SolveLine2(const double& X, const Vector2& P1, const Vector2& P2) {
	Vector2 max;
	Vector2 min;
	GetMinAndMaxX(min, max, P1, P2);

	return (P2.GetY() - P1.GetY()) / (P2.GetX() - P1.GetX()) * (X - P1.GetX()) + P1.GetY();
}

uint32_t MathHelper::Get2DIndex(const double& X, const double& Y, const uint32_t BufferWidth) {
	return static_cast<uint32_t>(Y * BufferWidth + X);
}

void MathHelper::GetMinAndMaxX(Vector2& Min, Vector2& Max, const Vector2& Start, const Vector2& End) {
	if (Start.GetX() > End.GetX()) {
		Min = End;
		Max = Start;
	}
	else {
		Min = Start;
		Max = End;
	}
}

void MathHelper::GetMinAndMaxY(Vector2& Min, Vector2& Max, const Vector2& Start, const Vector2& End) {
	if (Start.GetY() > End.GetY()) {
		Min = End;
		Max = Start;
	}
	else {
		Min = Start;
		Max = End;
	}
}
//
//Vector2 MathHelper::get_screen_coord(const vec4& a, const mat_4x4& transform, const mat_4x4& view_matrix,
//									 const mat_4x4& perspective_matrix, const uint32_t screen_width,
//									 const uint32_t screen_height) {
//	auto tmp = a;
//
//	// Create the ModelViewPerspective matrix
//	const auto m = perspective_matrix * view_matrix * transform;
//
//	// Transform the vertex to clip space.
//	tmp = m * tmp;
//
//	// Perform the perspective divide to get NDC space.
//	auto clip_space_x = tmp.GetX() / tmp.w;
//	auto clip_space_y = tmp.GetY() / tmp.w;
//
//	const auto half_width = screen_width / 2.0;
//	const auto half_height = screen_height / 2.0;
//
//	// Get window space for x and y by performing viewport and depth range transform.
//	clip_space_x = half_width * clip_space_x + (a.GetX() + half_width);
//	clip_space_y = half_height * clip_space_y + (a.GetY() + half_height);
//
//	return {clip_space_x, clip_space_y};
//}

double MathHelper::Sqrt(const double square) {
	/*double root = square / 3, diff = 1;
	if (square <= 0) return 0;
	do {
		const double last = root;
		root = (root + square / root) / 2;
		diff = root - last;
	}
	while (diff > MINDIFF || diff < -MINDIFF);
	*/
	return std::sqrt(square);
}

double MathHelper::Cot(const double& A) { return std::cos(A) / std::sin(A); }

double MathHelper::Deg2Rad(const double& Deg) { return Deg * PI / 180; }

