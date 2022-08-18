#include "MathHelper.h"

#include "Vector2.h"
#include "MathDefines.h"

float MathHelper::Deg2Rad(const float Degree) {
	return Degree * (static_cast<float>(PI) / 180.0f);
}

Vector2 MathHelper::GetParallelVec(const Vector2& A, const Vector2& B) {
	return {B.GetX() - A.GetX(), B.GetY() - A.GetY()};
}

Vector2 MathHelper::GetGradientVec(const Vector2& A, const Vector2& B) {
	return {A.GetY() - B.GetY(), B.GetX() - A.GetX()};
}

float MathHelper::LerpD(const float& A, const float& B, const float Ratio) {
	return (B - A) * static_cast<float>(Ratio) + A;
}

float MathHelper::LerpF(const float& A, const float& B, const float Ratio) {
	return static_cast<float>((B - A) * static_cast<float>(Ratio) + A);
}

uint32_t MathHelper::Floor(const float A) { return static_cast<uint32_t>(A); }
uint32_t MathHelper::Floor(const double A) { return static_cast<uint32_t>(A); }

float MathHelper::SolveLine(const float& CurX, const Vector2& P1, const Vector2& P2) {
	const float a = P1.GetY() - P2.GetY();
	const float b = P2.GetX() - P1.GetX();
	const float c = (P1.GetX() - P2.GetX()) * P1.GetY() + (P2.GetY() - P1.GetY()) * P1.GetX();

	return (a * CurX + c) / b;
}

float MathHelper::SolveLine2(const float& X, const Vector2& P1, const Vector2& P2) {
	Vector2 max;
	Vector2 min;
	GetMinAndMaxX(min, max, P1, P2);

	return (P2.GetY() - P1.GetY()) / (P2.GetX() - P1.GetX()) * (X - P1.GetX()) + P1.GetY();
}

uint32_t MathHelper::Get2DIndex(const float& X, const float& Y, const uint32_t BufferWidth) {
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

float MathHelper::Sqrt(const float square) {
	/*float root = square / 3, diff = 1;
	if (square <= 0) return 0;
	do {
		const float last = root;
		root = (root + square / root) / 2;
		diff = root - last;
	}
	while (diff > MINDIFF || diff < -MINDIFF);
	*/
	return std::sqrt(square);
}

float MathHelper::Cot(const float& A) { return std::cos(A) / std::sin(A); }

