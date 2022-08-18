#pragma once
#include <string>

#include "Vector2.h"

class Matrix4X4;

class Vector3 {
public:
	Vector3();
	Vector3(float X, float Y, float Z);
	~Vector3();

	Vector3(const Vector3& Other);
	Vector3(Vector3&& Other) noexcept;

	Vector3& operator=(const Vector3& Other);

	Vector3& operator=(Vector3&& Other) noexcept;

	Vector3 operator+(const Vector3& Other) const;
	Vector3& operator+=(const Vector3& Other);

	Vector3 operator*(float Other) const;
	Vector3& operator*=(float Other);

	Vector3 operator/(float Other) const;

	/**=== Getters and Setters ===*/
	float GetX() const;
	float GetY() const;
	float GetZ() const;

	Vector2 GetXy() const;

	/** Get the w component for the vector 3, this is the homogeneous coordinate and would be used for depth. */
	float GetW() const;
	void SetW(float NewW);

	void SetX(float NewX);
	void SetY(float NewY);
	void SetZ(float NewZ);

	Vector3& Translate(const Vector3& Other);
	Vector3& Scale(float Multiplier);
	Vector3& Scale(const Vector3& Other);
	Vector3& Rotate(const Matrix4X4& Other);

	static Vector3 XVector3() { return {1, 0, 0}; }
	static Vector3 YVector3() { return {0, 1, 0}; }
	static Vector3 ZVector3() { return {0, 0, 1}; }
	static Vector3 ZeroVector3() { return {0, 0, 0}; }
	static Vector3 OneVector3() { return {1, 1, 1}; }

	std::string ToString() const;

private:
	float Position[4]; // XYZW
};

