#include "Vector2.h"

#include <string>
#include <format>

#include "DebugHelper.h"
#include "DMath.h"


Vector2::Vector2(): Position{0, 0, 1} {}
Vector2::Vector2(const float X, const float Y): Position{X, Y, 1} {}
Vector2::~Vector2() = default;

Vector2::Vector2(const Vector2& Other): Position{} {
	this->SetX(Other.GetX());
	this->SetY(Other.GetY());
	this->SetZ(Other.GetZ());
}

Vector2::Vector2(Vector2&& Other) noexcept: Position{} {
	this->SetX(Other.GetX());
	this->SetY(Other.GetY());
	this->SetZ(Other.GetZ());
}

Vector2& Vector2::operator=(const Vector2& Other) {
	if (this == &Other) return *this;
	this->SetX(Other.GetX());
	this->SetY(Other.GetY());
	this->SetZ(Other.GetZ());
	return *this;
}

Vector2& Vector2::operator=(Vector2&& Other) noexcept {
	if (this == &Other) return *this;
	SetX(Other.GetX());
	SetY(Other.GetY());
	return *this;
}

Vector2 Vector2::operator+(const Vector2& Other) const { return { this->GetX() + Other.GetX(), this->GetY() + Other.GetY()}; }

Vector2& Vector2::operator+=(const Vector2& Other) {
	*this = *this + Other;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& Other) const {
	return {this->GetX() - Other.GetX(), this->GetY() - Other.GetY()};
}

Vector2& Vector2::operator-=(const Vector2& Other) {
	*this = *this - Other;
	return *this;
}

Vector2 Vector2::operator*(const float Other) const { return {this->GetX()*Other, this->GetY()*Other}; }
Vector2& Vector2::operator*=(const float Other) { *this = *this * Other; return *this; }

float Vector2::GetX() const { return this->Position[0]; }
float Vector2::GetY() const { return this->Position[1]; }

void Vector2::SetX(const float NewX) { this->Position[0] = NewX; }
void Vector2::SetY(const float NewY) { this->Position[1] = NewY; }

float Vector2::GetZ() const { return this->Position[2]; }
void Vector2::SetZ(const float Z) { this->Position[2] = Z; }

float Vector2::SquaredMagnitude() const { return this->GetX() * this->GetX() + this->GetY() * this->GetY(); }

Vector2& Vector2::Translate(const Vector2& Other) {
	this->SetX(GetX() + Other.GetX());
	this->SetY(GetY() + Other.GetY());

	return *this;
}

Vector2& Vector2::Scale(const float Multiplier) {
	SetX(GetX() * Multiplier);
	SetY(GetY() * Multiplier);

	return *this;
}

Vector2& Vector2::Scale(const Vector2& Other) {
	SetX(GetX() * Other.GetX());
	SetY(GetY() * Other.GetY());

	return *this;
}

std::string Vector2::ToString() const {
	return StringFormat("Vector2 {[X: %f, Y: %f] Homogenous: %f}", GetX(), GetY(), GetZ());
}

bool operator==(const Vector2& Lhs, const Vector2& Rhs) {
	return DMath::IsEqual(Lhs.GetX(), Rhs.GetX()) && DMath::IsEqual(Lhs.GetY(), Rhs.GetY()) && DMath::IsEqual(
		Lhs.GetZ(), Rhs.GetZ());
}

bool operator!=(const Vector2& Lhs, const Vector2& Rhs) { return !(Lhs == Rhs); }
