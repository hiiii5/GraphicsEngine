#pragma once
#include <string>

class Vector2 {
public:
	/**=== Constructors ===*/
	Vector2();
	Vector2(double X, double Y);
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

	Vector2 operator*(double Other) const;
	Vector2& operator*=(double Other);

	/**=== Getters and Setters ===*/
	double GetX() const;
	double GetY() const;

	void SetX(double NewX);
	void SetY(double NewY);

	/** Get the z component for the vector 2, this is the homogeneous coordinate and would be used for depth. */
	double GetHomogeneous() const;
	void SetHomogeneous(double Z);

	double SquaredMagnitude() const;

	Vector2& Translate(const Vector2& Other);
	Vector2& Scale(double Multiplier);
	Vector2& Scale(const Vector2& Other);

	friend bool operator==(const Vector2& Lhs, const Vector2& Rhs);
	friend bool operator!=(const Vector2& Lhs, const Vector2& Rhs);

	std::string ToString() const;

private:
	/** Array of */
	double Position[3]; // XYZ
};
