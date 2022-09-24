/**
 * \author Dustin Roden
 * \date 08/24/22
 * \brief Definitions for engine types and macros.
 */

#pragma once

#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>

#include "RenderHelper.h"

// Convert BBGGRRAA to AARRGGBB
#define BGRA_TO_ARGB(pixel) (                    \
	(((pixel) & 0xFF000000) >> 24)  /* Blue at the end */    |  \
	(((pixel) & 0x00FF0000) >> 8 )  /* Green comes next near the end */     |  \
	(((pixel) & 0x0000FF00) << 8 )  /* Red comes next, just before alpha */   |  \
	(((pixel) & 0x000000FF) << 24)) /* Alpha comes to the beginning to match AARRGGBB */


/**
 * \brief Converts degrees to radians.
 * \param Deg Degrees to convert to radians.
 * \return Radians of angle.
 */
static float Deg2Rad(const float Deg) {
	return Deg * ((float)M_PI / 180.0f);
}

/**
 * \brief Converts radians to degrees.
 * \param Rad Radians to convert to degrees.
 * \return Degrees of angle.
 */
static float Rad2Deg(const float Rad) {
	return (Rad * 180) / (float)M_PI;
}

static float LerpF(const float A, const float B, const float Ratio) {
	return (A * (1.0f - Ratio)) + (B * Ratio);
}

/**
 * \brief Truncates a float into an unsigned int
 * \param A Float to floor
 * \return Truncated float value.
 */
static unsigned Floor(const float A) {
	return static_cast<unsigned>(floorf(A));
}

static unsigned Round(const float A) {
	return static_cast<unsigned>(roundf(A));
}

static unsigned TwoD2OneD(const unsigned X, const unsigned Y, const unsigned MaxWidth) {
	return Y * MaxWidth + X;
}

static float Min(const float A, const float B) {
	return std::min(A, B);
}

static float Max(const float A, const float B) {
	return std::max(A, B);
}

static float Clamp(const float Value, const float Min, const float Max) {
	float ret = Value;
	if(ret < Min) ret = Min;
	if (ret > Max) ret = Max;

	return ret;
}

static float ClampAngle(const float Value) {
	auto ret = Value;
	ret = (float)std::fmod(ret, 360);
	if(ret < 0) ret += 360;

	return ret;
}

static unsigned ClampAndRound(const float Value, const float Min, const float Max) {
	const auto ret = Clamp(Value, Min, Max);
	return Floor(std::roundf(ret));
}

static float Cotan(const float A) {
	return std::cos(A) / std::sin(A);
}

static std::vector<float> Interpolate(const float I0, const float D0, const float I1, const float D1) {
	if ((int)I0 == (int)D0) return std::vector<float>{I0};

	std::vector<float> values;
	const auto a = (D1 - D0) / (I1 - I0);
	auto d = D0;

	for (int i = (int)I0; i < (int)I1; ++i) {
		values.emplace_back(d);
		d = d + a;
	}

	return values;
}

/**
 * \brief Swaps A with B and B with A.
 * \tparam T Type of variable to swap.
 * \param A First variable to swap.
 * \param B Second variable to swap.
 */
template<typename T>
static void Swap(T& A, T& B) {
	auto temp = A;
	A = B;
	B = temp;
}

/**
 * \brief Vector 2D consisting of X and Y as floats. Provides helpers and operator overloads for easy math.
 */
struct Vec2F {
	Vec2F() : X(0.0f), Y(0.0f), Z(1) {}

	Vec2F(const float X, const float Y)
		: X(X),
		  Y(Y), Z(1) {}

	float X, Y, Z;

#pragma region Operators
	Vec2F operator+(const float C) const {
		return {X + C, Y + C};
	}
	Vec2F operator+(const Vec2F& V) const {
		return {X + V.X, Y + V.Y};
	}

	Vec2F operator-(const Vec2F& V) const {
		return {X - V.X, Y - V.Y};
	}

	Vec2F& operator+=(const float C) {
		*this = *this + C;
		return *this;
	}
	Vec2F& operator+=(const Vec2F& V) {
		*this = *this + V;
		return *this;
	}

	Vec2F operator*(const float C) const {
		return {X * C, Y * C};
	}
	float operator*(const Vec2F& V) const {
		return X * V.Y - Y * V.X;
	}

	Vec2F& operator*=(const float C) {
		*this = *this * C;
		return *this;
	}

	Vec2F operator/(const float C) const {
		return {X / C, Y / C};
	}

	Vec2F& operator/=(const float C) {
		*this = *this / C;
		return *this;
	}

	friend bool operator==(const Vec2F& Lhs, const Vec2F& Rhs) {
		return std::abs(Lhs.X - Rhs.X) < 0.001f
			&& std::abs(Lhs.Y - Rhs.Y) < 0.001f;
	}

	friend bool operator!=(const Vec2F& Lhs, const Vec2F& Rhs) { return !(Lhs == Rhs); }
#pragma endregion

#pragma region Static Helpers
	static float DotProduct(const Vec2F& A, const Vec2F& B) {
		return A.X * B.X + A.Y * B.Y;
	}

	static float CrossProduct(const Vec2F& A, const Vec2F& B) {
		return A * B;
	}
#pragma endregion
};

/**
 * \brief Vector 3D consisting of X, Y, and Z as floats. Provides helpers and operator overloads for easy math.
 */
struct Vec3F {
	Vec3F(): X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}

	Vec3F(const float X, const float Y, const float Z)
		: X(X),
		  Y(Y),
		  Z(Z),
		  W(1.0f) {}

	float X, Y, Z, W;

#pragma region Operators
	Vec3F operator+(const float C) const {
		return {X + C, Y + C, Z + C};
	}
	Vec3F operator+(const Vec2F& V) const {
		return {X + V.X, Y + V.Y, Z};
	}
	Vec3F operator+(const Vec3F& V) const {
		return {X + V.X, Y + V.Y, Z + V.Z};
	}

	Vec3F& operator+=(const float C) {
		*this = *this + C;
		return *this;
	}
	Vec3F& operator+=(const Vec2F& V) {
		*this = *this + V;
		return *this;
	}
	Vec3F& operator+=(const Vec3F& V) {
		*this = *this + V;
		return *this;
	}

	Vec3F operator-(const float C) const {
		return {X - C, Y - C, Z - C};
	}
	Vec3F operator-(const Vec3F& V) const {
		return {X - V.X, Y - V.Y, Z - V.Z};
	}

	Vec3F& operator-=(const float C) {
		*this = *this - C;
		return *this;
	}
	Vec3F& operator-=(const Vec3F& V) {
		*this = *this - V;
		return *this;
	}

	Vec3F operator*(const float C) const {
		return {X * C, Y * C, Z * C};
	}
	Vec3F operator*(const Vec3F& V) const {
		return {
			Y * V.Z - Z * V.Y,
			Z * V.X - X * V.Z,
			X * V.Y - Y * V.X
		};
	}

	Vec3F operator/(const float C) const {
		return {X / C, Y / C, Z / C};
	}

	Vec3F& operator/=(const float C) {
		*this = *this / C;
		return *this;
	}
#pragma endregion

#pragma region Static Helpers
	static float DotProduct(const Vec3F& A, const Vec3F& B) {
		return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
	}

	static Vec3F CrossProduct(const Vec3F& A, const Vec3F& B) {
		return A * B;
	}

	static Vec3F Translate(const Vec3F& Start, const Vec3F& Offset) {
		return Start + Offset;
	}

	static Vec3F Scale(const Vec3F& Start, const float Scale) {
		return Start * Scale;
	}

	static Vec3F Scale(const Vec3F& Start, const Vec3F& ScaleFactors) {
		return {Start.X * ScaleFactors.X, Start.Y * ScaleFactors.Y, Start.Z * ScaleFactors.Z};
	}

	static float Distance(const Vec3F& Start, const Vec3F& End) {
		return sqrt((End.X - Start.X * End.X - Start.X)
					+ (End.Y - Start.Y * End.Y - Start.Y)
					+ (End.Z - Start.Z * End.Z - Start.Z));
	}
#pragma endregion
};

/**
 * \brief A 4x4 matrix of floating point values.
 */
struct Mat4 {
	Mat4() {
		*this = LoadIdentity();
	}

	explicit Mat4(std::vector<float> M)
		: M(std::move(M)) {}

#pragma region Operators
	float& operator[](const unsigned Index) {
		if (Index > M.size()) { throw std::exception("Array out of bounds"); }
		return M[Index];
	}

	Mat4 operator+(const Mat4& Other) const {
		std::vector<float> tmp{};
		tmp.assign(16, 0.0f);
		for (int i = 0; i < 16; ++i) {
			tmp[i] = M[i] + Other.M[i];
		}

		return Mat4(tmp);
	}

	Mat4& operator+=(const Mat4& Other) {
		*this = *this + Other;
		return *this;
	}

	Mat4 operator*(const Mat4& Other) const {
		std::vector<float> tmp{};
		tmp.assign(16, 0.0f);

		// Row 1
		tmp[0] = this->M[0] * Other.M[0] + this->M[1] * Other.M[4] + this->M[2] * Other.M[8] + this->M[3] * Other.M[12];
		tmp[1] = this->M[0] * Other.M[1] + this->M[1] * Other.M[5] + this->M[2] * Other.M[9] + this->M[3] * Other.M[13];
		tmp[2] = this->M[0] * Other.M[2] + this->M[1] * Other.M[6] + this->M[2] * Other.M[10] + this->M[3] * Other.M[14];
		tmp[3] = this->M[0] * Other.M[3] + this->M[1] * Other.M[7] + this->M[2] * Other.M[11] + this->M[3] * Other.M[15];

		// Row 2
		tmp[4] = this->M[4] * Other.M[0] + this->M[5] * Other.M[4] + this->M[6] * Other.M[8] + this->M[7] * Other.M[12];
		tmp[5] = this->M[4] * Other.M[1] + this->M[5] * Other.M[5] + this->M[6] * Other.M[9] + this->M[7] * Other.M[13];
		tmp[6] = this->M[4] * Other.M[2] + this->M[5] * Other.M[6] + this->M[6] * Other.M[10] + this->M[7] * Other.M[14];
		tmp[7] = this->M[4] * Other.M[3] + this->M[5] * Other.M[7] + this->M[6] * Other.M[11] + this->M[7] * Other.M[15];

		// Row 3
		tmp[8] = this->M[8] * Other.M[0] + this->M[9] * Other.M[4] + this->M[10] * Other.M[8] + this->M[11] * Other.M[12];
		tmp[9] = this->M[8] * Other.M[1] + this->M[9] * Other.M[5] + this->M[10] * Other.M[9] + this->M[11] * Other.M[13];
		tmp[10] = this->M[8] * Other.M[2] + this->M[9] * Other.M[6] + this->M[10] * Other.M[10] + this->M[11] * Other.M[14];
		tmp[11] = this->M[8] * Other.M[3] + this->M[9] * Other.M[7] + this->M[10] * Other.M[11] + this->M[11] * Other.M[15];

		// Row 4
		tmp[12] = this->M[12] * Other.M[0] + this->M[13] * Other.M[4] + this->M[14] * Other.M[8] + this->M[15] * Other.M[12];
		tmp[13] = this->M[12] * Other.M[1] + this->M[13] * Other.M[5] + this->M[14] * Other.M[9] + this->M[15] * Other.M[13];
		tmp[14] = this->M[12] * Other.M[2] + this->M[13] * Other.M[6] + this->M[14] * Other.M[10] + this->M[15] * Other.M[14];
		tmp[15] = this->M[12] * Other.M[3] + this->M[13] * Other.M[7] + this->M[14] * Other.M[11] + this->M[15] * Other.M[15];

		return Mat4(tmp);
	}

	Vec3F Project(const Vec3F& V) const {
		Vec3F tmp{};

		tmp.X = this->M[0] * V.X + this->M[4] * V.Y + this->M[8]  * V.Z + this->M[12] * V.W;
		tmp.Y = this->M[1] * V.X + this->M[5] * V.Y + this->M[9]  * V.Z + this->M[13] * V.W;
		tmp.Z = this->M[2] * V.X + this->M[6] * V.Y + this->M[10] * V.Z + this->M[14] * V.W;
		tmp.W = this->M[3] * V.X + this->M[7] * V.Y + this->M[11] * V.Z + this->M[15] * V.W;

		return tmp;
	}

	Mat4& operator*=(const Mat4& Other) {
		*this = *this * Other;
		return *this;
	}
#pragma endregion

#pragma region Member Functions
	/**
	 * \brief Assigns the identity matrix to this matrix.
	 * \return Identity matrix.
	 */
	Mat4& LoadIdentity() {
		M.assign(16, 0.0f);
		M[0] = M[5] = M[10] = M[15] = 1.0f;

		return *this;
	}

	/**
	 * \brief Displaces this matrix by the given translation amounts in X, Y, and Z.
	 * \param Translation Displacement in X, Y, and Z to translate by.
	 * \return Translated matrix
	 */
	Mat4& Translate(const Vec3F& Translation) {
		const auto _ = Mat4({
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			Translation.X, Translation.Y, Translation.Z, 1
		});

		*this = _ * *this;
		return *this;
	}

	/**
	 * \brief Scales this matrix in its X, Y and Z by the given scaling factors.
	 * \param ScalingFactor Factor in X, Y, and Z to scale by.
	 * \return Scaled matrix.
	 */
	Mat4& Scale(const Vec3F& ScalingFactor) {
		const auto _ = Mat4({
			ScalingFactor.X, 0, 0, 0,
			0, ScalingFactor.Y, 0, 0,
			0, 0, ScalingFactor.Z, 0,
			0, 0, 0, 1
		});

		*this *= _;
		return *this;
	}

	/**
	 * \brief Rotates this matrix by the given X, Y, and Z degree angles with the correct composition.
	 * \param Rotation Degrees in X, Y, and Z to rotate by.
	 * \return Rotated matrix.
	 */
	Mat4& Rotate(const Vec3F& Rotation) {
		// Compose the rotation matrices in order of Z, Y, X to get to the final rotation of this matrix.
		*this *= GetZRotation(Deg2Rad(ClampAngle(Rotation.Z)));
		*this *= GetYRotation(Deg2Rad(ClampAngle(Rotation.Y)));
		*this *= GetXRotation(Deg2Rad(ClampAngle(Rotation.X)));

		return *this;
	}

	/**
	 * \brief Gets the first row of the matrix, the right facing vector.
	 * \return The first row of the matrix.
	 */
	Vec3F GetRightVector() {
		return { M[0], M[1], M[2] };
	}

	/**
	 * \brief Gets the first row of the matrix, the up facing vector.
	 * \return The second row of the matrix.
	 */
	Vec3F GetUpVector() {
		return { M[4], M[5], M[6] };
	}

	/**
	 * \brief Gets the first row of the matrix, the forward facing vector.
	 * \return The third row of the matrix.
	 */
	Vec3F GetForwardVector() {
		return { M[8], M[9], M[10] };
	}

	Vec3F GetPosition() const {
		return {M[12], M[13], M[14]};
	}

	Vec3F GetScale() const {
		return {M[0], M[5], M[10]};
	}

	/**
	 * \brief Flips a matrix along its identity.
	 * \return Flipped matrix along its identity.
	 */
	Mat4 GetTranspose() const {
		Mat4 m = *this;

		// Do nothing for identity coordinates. Interchange the outsides, and then come in to finish.
		float tmp = m[1];
		m[1] = m[4];
		m[4] = tmp;

		tmp = m[2];
		m[2] = m[8];
		m[8] = tmp;

		tmp = m[3];
		m[3] = m[12];
		m[12] = tmp;

		tmp = m[7];
		m[7] = m[13];
		m[13] = tmp;

		tmp = m[11];
		m[11] = m[14];
		m[14] = tmp;

		tmp = m[6];
		m[6] = m[9];
		m[9] = tmp;

		return m;
	}

	/**
	 * \brief Flips this matrix along its identity.
	 * \return This matrix flipped along its identity.
	 */
	Mat4& Transpose() {
		*this = this->GetTranspose();
		return *this;
	}

	/**
	 * \brief Calculates the inverse of this matrix.
	 * \return copy of the inverse of this matrix.
	 */
	Mat4 GetInverse() const {
		Mat4 result;

		float d12 = (this->M[8] * this->M[13] - this->M[12] * this->M[9]);
		float d13 = (this->M[8] * this->M[14] - this->M[12] * this->M[10]);
		float d23 = (this->M[9] * this->M[14] - this->M[13] * this->M[10]);
		float d24 = (this->M[9] * this->M[15] - this->M[13] * this->M[11]);
		float d34 = (this->M[10] * this->M[15] - this->M[14] * this->M[11]);
		float d41 = (this->M[11] * this->M[12] - this->M[15] * this->M[8]);

		float tmp[16];
		tmp[0] = (this->M[5] * d34 - this->M[6] * d24 + this->M[7] * d23);
		tmp[1] = -(this->M[4] * d34 + this->M[6] * d41 + this->M[7] * d13);
		tmp[2] = (this->M[4] * d24 + this->M[5] * d41 + this->M[7] * d12);
		tmp[3] = -(this->M[4] * d23 - this->M[5] * d13 + this->M[6] * d12);

		const float determinant = this->M[0] * tmp[0] + this->M[1] * tmp[1] + this->M[2] * tmp[2] + this->M[3] * tmp[
			3];
		if (determinant == 0.0f) { result = Mat4{}; }
		else {
			const float invDet = 1.0f / determinant;
			tmp[0] *= invDet;
			tmp[1] *= invDet;
			tmp[2] *= invDet;
			tmp[3] *= invDet;
			tmp[4] = -(this->M[1] * d34 - this->M[2] * d24 + this->M[3] * d23) * invDet;
			tmp[5] = (this->M[0] * d34 + this->M[2] * d41 + this->M[3] * d13) * invDet;
			tmp[6] = -(this->M[0] * d24 + this->M[1] * d41 + this->M[3] * d12) * invDet;
			tmp[7] = (this->M[0] * d23 - this->M[1] * d13 + this->M[2] * d12) * invDet;

			d12 = this->M[0] * this->M[5] - this->M[4] * this->M[1];
			d13 = this->M[0] * this->M[6] - this->M[4] * this->M[2];
			d23 = this->M[1] * this->M[6] - this->M[5] * this->M[2];
			d24 = this->M[1] * this->M[7] - this->M[5] * this->M[3];
			d34 = this->M[2] * this->M[7] - this->M[6] * this->M[3];
			d41 = this->M[3] * this->M[4] - this->M[7] * this->M[0];

			tmp[8] = (this->M[13] * d34 - this->M[14] * d24 + this->M[15] * d23) * invDet;
			tmp[9] = -(this->M[12] * d34 + this->M[14] * d41 + this->M[15] * d13) * invDet;
			tmp[10] = (this->M[12] * d24 + this->M[13] * d41 + this->M[15] * d12) * invDet;
			tmp[11] = -(this->M[12] * d23 - this->M[13] * d13 + this->M[14] * d12) * invDet;
			tmp[12] = -(this->M[9] * d34 - this->M[10] * d24 + this->M[11] * d23) * invDet;
			tmp[13] = (this->M[8] * d34 + this->M[10] * d41 + this->M[11] * d13) * invDet;
			tmp[14] = -(this->M[8] * d24 + this->M[9] * d41 + this->M[11] * d12) * invDet;
			tmp[15] = (this->M[8] * d23 - this->M[9] * d13 + this->M[10] * d12) * invDet;
			memcpy(&result.M[0], tmp, 16 * sizeof(float));
		}

		return result.Transpose();
	}

	/**
	 * \brief Inverts this matrix using GetInverse.
	 * \return This matrix inverted.
	 */
	Mat4& Invert() {
		*this = this->GetInverse();
		return *this;
	}
	
#pragma endregion

private:
	// Valid for index 0-15, in row major format.
	std::vector<float> M;

#pragma region Static Helpers
public:
	/**
	 * \brief Creates a rotation matrix in X by the given rotation amount.
	 * \param Radians Angle in radians of rotation.
	 * \return Rotation matrix for given angle.
	 */
	static Mat4 GetXRotation(const float Radians) {
		return Mat4({
			1, 0, 0, 0,
			0, std::cos(Radians), -std::sin(Radians), 0,
			0, std::sin(Radians), std::cos(Radians), 0,
			0, 0, 0, 1
		});
	}

	/**
	 * \brief Creates a rotation matrix in Y by the given rotation amount.
	 * \param Radians Angle in radians of rotation.
	 * \return Rotation matrix for given angle.
	 */
	static Mat4 GetYRotation(const float Radians) {
		return Mat4({
			std::cos(Radians), 0, -std::sin(Radians), 0,
			0, 1, 0, 0,
			std::sin(Radians), 0, std::cos(Radians), 0,
			0, 0, 0, 1
		});
	}

	/**
	 * \brief Creates a rotation matrix in Z by the given rotation amount.
	 * \param Radians Angle in radians of rotation.
	 * \return Rotation matrix for given angle.
	 */
	static Mat4 GetZRotation(const float Radians) {
		return Mat4({
			std::cos(Radians), -std::sin(Radians), 0, 0,
			std::sin(Radians), std::cos(Radians), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		});
	}

	/**
	 * \brief Calculates the cross product of Lhs by Rhs.
	 * \param Lhs Left hand side of the cross product operation.
	 * \param Rhs Right hand side of the the cross product operation.
	 * \return Matrix result from cross product operation.
	 */
	static Mat4 CrossProduct(const Mat4& Lhs, const Mat4& Rhs) {
		return Lhs * Rhs;
	}
#pragma endregion
};

struct Color {
	Color() { *this = Color(Color::White); }

	Color(const float A, const float R, const float G, const float B)
		: A(Clamp(A, 0, 255)),
		  R(Clamp(R, 0, 255)),
		  G(Clamp(G, 0, 255)),
		  B(Clamp(B, 0, 255)) {}

	explicit Color(const unsigned C): A((float)((C & 0xFF000000) >> 24)), R((float)((C & 0x00FF0000) >> 16)), G((float)((C & 0x0000FF00) >> 8)), B((float)(C & 0x000000FF)) {}

	float A, R, G, B;

	unsigned Get() const {
		return Floor(A) << 24 | Floor(R) << 16 | Floor(G) << 8 | Floor(B);
	}

	static Color AlphaBlend(const Color& Foreground, const Color& Background) {
		auto red = LerpF(Background.R, Foreground.R, Foreground.A / 255.0f);
		auto green = LerpF(Background.G, Foreground.G, Foreground.A / 255.0f);
		auto blue = LerpF(Background.B, Foreground.B, Foreground.A / 255.0f);

		red = Clamp(red, 0, 255.0f);
		green = Clamp(green, 0, 255.0f);
		blue = Clamp(blue, 0, 255.0f);

		return Color{ Floor(Foreground.A) << 24 | Floor(red) << 16 | Floor(green) << 8 | Floor(blue) };
	}

	Color operator*(const float Other) const {
		const auto newR = Clamp(this->R * Other, 0.0f, 255.0f);
		const auto newG = Clamp(this->G * Other, 0.0f, 255.0f);
		const auto newB = Clamp(this->B * Other, 0.0f, 255.0f);
		return Color(this->A, newR, newG, newB);
	}

	Color operator*(const Color Other) const {
		const auto newR = Clamp(this->R * Other.R, 0.0f, 255.0f);
		const auto newG = Clamp(this->G * Other.G, 0.0f, 255.0f);
		const auto newB = Clamp(this->B * Other.B, 0.0f, 255.0f);
		return Color(this->A, newR, newG, newB);
	}

	Color& operator*=(const float Other) {
		*this = *this * Other;
		return *this;
	}

	Color& operator*=(const Color Other) {
		*this = *this * Other;
		return *this;
	}

	static constexpr unsigned Black = 0xFF000000;
	static constexpr unsigned Red = 0xFFFF0000;
	static constexpr unsigned Green = 0xFF00FF00;
	static constexpr unsigned Blue = 0xFF0000FF;
	static constexpr unsigned White = 0xFFFFFFFF;
};

struct Vert {

public:
	Vert() : Pos({}), C({}), Norm({}), Light({0, 0, 0}) {}

	Vert(const Vec3F& Pos, const Color& C, const Vec3F& Norm = Vec3F())
		: Pos(Pos),
		C(C),
		Norm(Norm),
		Light({0, 0, 0}) {}

	Vec3F Pos;
	Color C;
	Vec3F Norm;
	Vec3F Light;
};

struct Camera {
	Camera(const float NearPlane, const float FarPlane, const float FieldOfView, const unsigned ScreenWidth,
		const unsigned ScreenHeight, Mat4 WorldTransform)
		: NearPlane(NearPlane),
		  FarPlane(FarPlane),
		  FieldOfView(FieldOfView),
		  ScreenWidth(ScreenWidth),
		  ScreenHeight(ScreenHeight),
		  WorldTransform(std::move(WorldTransform)) {

		const auto ratio = static_cast<float>(ScreenHeight) / static_cast<float>(ScreenWidth);
		const auto halfFov = FieldOfView / 2;
		const auto yScale = std::cos(halfFov) / std::sin(halfFov);
		const auto xScale = yScale * ratio;

		const auto planeDist = FarPlane - NearPlane;
		const auto zScale = FarPlane / (planeDist);
		const auto zTrans = -(FarPlane * NearPlane) / (planeDist);

		PerspectiveProjection = Mat4({
			xScale, 0, 0, 0,
			0, yScale, 0, 0,
			0, 0, zScale, 1,
			0, 0, zTrans, 0
		});
	}

	float NearPlane, FarPlane, FieldOfView;
	unsigned ScreenWidth, ScreenHeight;

	Mat4 WorldTransform;
	Mat4 PerspectiveProjection;

	Mat4 GetViewMatrix() const {
		return this->WorldTransform.GetInverse();
	}

	Mat4 GetPerspectiveProjection() const {
		return PerspectiveProjection;
	}

	static void Perspective(Vert& V, const Mat4& T, const Camera& C) {
		auto newPos = T.Project(V.Pos);

		newPos = C.GetViewMatrix().Project(newPos);

		// Perform perspective projection.
		newPos = C.GetPerspectiveProjection().Project(newPos);

		// Perform perspective divide. Take ndc space to screen space.
		newPos.X /= newPos.W;
		newPos.Y /= newPos.W;
		newPos.Z /= newPos.W;

		newPos.X = (newPos.X * 0.5f + 0.5f) * (float)C.ScreenWidth;
		newPos.Y = (1.0f - (newPos.Y * 0.5f + 0.5f)) * (float)C.ScreenHeight;

		V.Pos = newPos;
	}

	static Vec2F WorldToScreen(const Camera& C, const Vert& P, Mat4& PTransform) {
		// Rotate the parent object.
		Vert p0 = P;

		//RenderHelper::VertexShader(p0, PTransform, C);

		Perspective(p0, PTransform, C);

		Vec2F ret = { p0.Pos.X, p0.Pos.Y };
		ret.Z = p0.Pos.W;

		return ret;
	}
};

static bool Within(const float X)
{
	return 0 <= X && X <= 1;
}

static void Barycentric(const Vec2F P, const Vec2F A, const Vec2F B, const Vec2F C, float& U, float& V, float& W)
{
	// Cramer's rule...
	const Vec2F v0 = B - A;
	const Vec2F v1 = C - A;
	const Vec2F v2 = P - A;

	const float d00 = Vec2F::DotProduct(v0, v0);
	const float d01 = Vec2F::DotProduct(v0, v1);
	const float d11 = Vec2F::DotProduct(v1, v1);
	const float d20 = Vec2F::DotProduct(v2, v0);
	const float d21 = Vec2F::DotProduct(v2, v1);

	const float denom = d00 * d11 - d01 * d01;

	V = (d11 * d20 - d01 * d21) / denom;
	W = (d00 * d21 - d01 * d20) / denom;
	U = 1.0f - V - W;
}

//static void CalculateBarycentricCoords(float& U, float& V, float& W, const Vec2F& Point, const std::vector<Vec3F>& Vertices) {
//	const Vec2F v0 = Vertices[1] - Vertices[0];
//	const Vec2F v1 = Vertices[2] - Vertices[0];
//	const Vec2F v2 = Point - Vertices[0];
//	const float d00 = v0 * v0;
//	const float d01 = v0 * v1;
//	const float d11 = v1 * v1;
//	const float d20 = v2 * v0;
//	const float d21 = v2 * v1;
//	const float denom = d00 * d11 - d01 * d01;
//	V = (d11 * d20 - d01 * d21) / denom;
//	W = (d00 * d21 - d01 * d20) / denom;
//	U = 1.0f - V - W;
//}
//
//static Vec2F CalculateTextureCoords(const std::vector<Vec3F>& TriangleWorld, const std::vector<Vec2F>& Uv, const Vec2F& PointWorld) {
//	float u, v, w;
//	CalculateBarycentricCoords(u, v, w, PointWorld, TriangleWorld);
//
//	const Vec2F textureCoords =
//		Uv[0] * u +
//		Uv[1] * v +
//		Uv[2] * w;
//
//	return textureCoords;
//}

static float ImplicitLineEquation(const Vec2F& A, const Vec2F& B, const Vec2F& P) {
	return (A.Y - B.Y) * P.X + (B.X - A.X) * P.Y + (A.X * B.Y - A.Y * B.X);
}

static Vec3F GetBarycentric(const Vec2F& P, const Vec2F& A, const Vec2F& B, const Vec2F& C) {
	// A
	const auto abToPDist = ImplicitLineEquation(A, B, P);
	const auto abToCDist = ImplicitLineEquation(A, B, C);
	const auto weightC = abToPDist / abToCDist;

	// B
	const auto acToPDist = ImplicitLineEquation(C, A, P);
	const auto acToBDist = ImplicitLineEquation(C, A, B);
	const auto weightB = acToPDist / acToBDist;

	// C
	const auto bcToPDist = ImplicitLineEquation(B, C, P);
	const auto bcToADist = ImplicitLineEquation(B, C, A);
	const auto weightA = bcToPDist / bcToADist;

	return{weightA, weightB, weightC};
}

static float Edge(const Vec2F& A, const Vec2F& B, const Vec2F& P) {
	const auto a = P - A;
	const auto b = B - A;

	return Vec2F::CrossProduct(a, b);
}

