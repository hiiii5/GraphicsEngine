#pragma once
#include <string>

class Vector2 {
public:
	/**=== Constructors ===*/
	Vector2();
	Vector2(float X, float Y);
	~Vector2();

	/**=== Copy and Move ===*/
	Vector2(const Vector2& Other);
	Vector2(Vector2&& Other) noexcept;
	Vector2& operator=(const Vector2& Other);
	Vector2& operator=(Vector2&& Other) noexcept;

	Vector2 operator+(const Vector2& Other) const;
	Vector2& operator+=(const Vector2& Other);

	Vector2 operator-(const Vector2& Other) const;
	Vector2& operator-=(const Vector2& Other);

	Vector2 operator*(float Other) const;
	Vector2& operator*=(float Other);

	/**=== Getters and Setters ===*/
	float GetX() const;
	float GetY() const;

	void SetX(float NewX);
	void SetY(float NewY);

	/** Get the z component for the vector 2, this is the homogeneous coordinate and would be used for depth. */
	float GetZ() const;
	void SetZ(float Z);

	float SquaredMagnitude() const;

	Vector2& Translate(const Vector2& Other);
	Vector2& Scale(float Multiplier);
	Vector2& Scale(const Vector2& Other);

	friend bool operator==(const Vector2& Lhs, const Vector2& Rhs);
	friend bool operator!=(const Vector2& Lhs, const Vector2& Rhs);

	std::string ToString() const;

private:
	/** Array of */
	float Position[3]; // XYZ
};
