#pragma once
#include <cstdint>

#include "Matrix4x4.h"
#include "Vector2.h"


class MathHelper {
public:
	static Vector2 GetParallelVec(const Vector2& A, const Vector2& B);

	static Vector2 GetGradientVec(const Vector2& A, const Vector2& B);

	static float LerpD(const float& A, const float& B, float Ratio);

	static float LerpF(const float& A, const float& B, float Ratio);

	static uint32_t Floor(float A);

	static float SolveLine(const float& CurX, const Vector2& P1, const Vector2& P2);

	static float SolveLine2(const float& X, const Vector2& P1, const Vector2& P2);

	static uint32_t Get2DIndex(const float& X, const float& Y, uint32_t BufferWidth);

	static void GetMinAndMaxX(Vector2& Min, Vector2& Max, const Vector2& Start, const Vector2& End);

	static void GetMinAndMaxY(Vector2& Min, Vector2& Max, const Vector2& Start, const Vector2& End);

	/*static Vector2 get_screen_coord(const vec4& a, const mat_4x4& transform, const mat_4x4& view_matrix,
								 const mat_4x4& perspective_matrix, uint32_t screen_width, uint32_t screen_height);*/

	// Credit of Weather Vane https://stackoverflow.com/questions/29018864/any-way-to-obtain-square-root-of-a-number-without-using-math-h-and-sqrt
	static float Sqrt(float square);

	static float Cot(const float& A);

	static float Deg2Rad(const float& Deg);

	static Matrix4X4 MatrixMultiply(const Matrix4X4& A, const Matrix4X4& B);
};
