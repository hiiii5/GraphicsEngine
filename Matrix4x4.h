#pragma once
#include <string>


class Vector3;

class Matrix4X4 {
public:
	Matrix4X4();

	explicit Matrix4X4(const float NewM[16]);
	~Matrix4X4();

	/**=== Copy and Move ===*/
	Matrix4X4(const Matrix4X4& Other);
	Matrix4X4& operator=(const Matrix4X4& Other);
	Matrix4X4& operator=(Matrix4X4&& Other) noexcept;

	Matrix4X4 operator+(const Matrix4X4& Other) const;
	Matrix4X4& operator+=(const Matrix4X4& Other);

	Matrix4X4 operator*(const Matrix4X4& Other) const;
	Vector3 operator*(const Vector3& Other) const;
	Matrix4X4& operator*=(const Matrix4X4& Other);

	Matrix4X4& Transform(const Matrix4X4& Other);

	Matrix4X4& Translate(const Vector3& Translation);
	Matrix4X4& Scale(const Vector3& Scale);
	// TODO Change to Rotator
	Matrix4X4& Rotate(const Vector3& Rotation);

	Vector3 GetPosition();
	Matrix4X4& SetPosition(const Vector3& Pos);
	Matrix4X4& SetScale(const Vector3& Scale);

	Matrix4X4 Transpose() const;

	Matrix4X4 Inverse() const;
	Matrix4X4& Invert();

	Matrix4X4& LoadIdentity();

	static Matrix4X4 GetRotationX(float Radians);
	static Matrix4X4 GetRotationY(float Radians);
	static Matrix4X4 GetRotationZ(float Radians);

	std::string ToString() const;

	float& operator[](unsigned int Index);

	friend bool operator==(const Matrix4X4& Lhs, const Matrix4X4& Rhs);
	friend bool operator!=(const Matrix4X4& Lhs, const Matrix4X4& Rhs);

private:
	float M[16];
};
