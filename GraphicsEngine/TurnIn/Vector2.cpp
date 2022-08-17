#include "Vector2.h"

#include <string>
#include <format>

#include "DebugHelper.h"
#include "DMath.h"


Vector2::Vector2(): Position{0, 0, 1} {}
Vector2::Vector2(const double X, const double Y): Position{X, Y, 1} {}
Vector2::~Vector2() = default;

Vector2::Vector2(const Vector2& Other): Position{} {
	this->SetX(Other.GetX());
	this->SetY(Other.GetY());
	this->SetHomogeneous(Other.GetHomogeneous());
}

Vector2::Vector2(Vector2&& Other) noexcept: Position{} {
	this->SetX(Other.GetX());
	this->SetY(Other.GetY());
	this->SetHomogeneous(Other.GetHomogeneous());
}

Vector2& Vector2::operator=(const Vector2& Other) {
	if (this == &Other) return *this;
	this->SetX(Other.GetX());
	this->SetY(Other.GetY());
	this->SetHomogeneous(Other.GetHomogeneous());
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

Vector2 Vector2::operator*(const double Other) const { return {this->GetX()*Other, this->GetY()*Other}; }
Vector2& Vector2::operator*=(const double Other) { *this = *this * Other; return *this; }

double Vector2::GetX() const { return this->Position[0]; }
double Vector2::GetY() const { return this->Position[1]; }

void Vector2::SetX(const double NewX) { this->Position[0] = NewX; }
void Vector2::SetY(const double NewY) { this->Position[1] = NewY; }

double Vector2::GetHomogeneous() const { return this->Position[2]; }
void Vector2::SetHomogeneous(const double Z) { this->Position[2] = Z; }

double Vector2::SquaredMagnitude() const { return this->GetX() * this->GetX() + this->GetY() * this->GetY(); }

Vector2& Vector2::Translate(const Vector2& Other) {
	this->SetX(GetX() + Other.GetX());
	this->SetY(GetY() + Other.GetY());

	return *this;
}

Vector2& Vector2::Scale(const double Multiplier) {
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
	return Stringf("Vector2 {[X: %f, Y: %f] Homogenous: %f}", GetX(), GetY(), GetHomogeneous());
}

bool operator==(const Vector2& Lhs, const Vector2& Rhs) {
	return DMath::IsEqual(Lhs.GetX(), Rhs.GetX()) && DMath::IsEqual(Lhs.GetY(), Rhs.GetY()) && DMath::IsEqual(
		Lhs.GetHomogeneous(), Rhs.GetHomogeneous());
}

bool operator!=(const Vector2& Lhs, const Vector2& Rhs) { return !(Lhs == Rhs); }
