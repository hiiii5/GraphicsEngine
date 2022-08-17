#pragma once
#include <string>


class Vector3;

class Matrix4X4 {
public:
	Matrix4X4();

	explicit Matrix4X4(const double NewM[16]);
	~Matrix4X4();

	/**=== Copy and Move ===*/
	Matrix4X4(const Matrix4X4& Other);
	Matrix4X4(Matrix4X4&& Other) noexcept;
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

	static Matrix4X4 GetRotationX(double Radians);
	static Matrix4X4 GetRotationY(double Radians);
	static Matrix4X4 GetRotationZ(double Radians);

	std::string ToString() const;

	double& operator[](unsigned int Index) const;

	friend bool operator==(const Matrix4X4& Lhs, const Matrix4X4& Rhs);
	friend bool operator!=(const Matrix4X4& Lhs, const Matrix4X4& Rhs);

private:
	double* M;
};
