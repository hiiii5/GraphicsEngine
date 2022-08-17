#include "Vector3.h"

#include "DebugHelper.h"
#include "Matrix4x4.h"

Vector3::Vector3() : Position{0, 0, 0, 1} {}
Vector3::Vector3(const double X, const double Y, const double Z) : Position{X, Y, Z, 1} {}
Vector3::~Vector3() = default;

Vector3::Vector3(const Vector3& Other) : Position{Other.GetX(), Other.GetY(), Other.GetZ(), Other.GetW()} {}

Vector3::Vector3(Vector3&& Other) noexcept : Position{
	Other.GetX(), Other.GetY(), Other.GetZ(), Other.GetW()
} {}

Vector3& Vector3::operator=(const Vector3& Other) {
	if (this == &Other) return *this;
	SetX(Other.GetX());
	SetY(Other.GetY());
	SetZ(Other.GetZ());
	SetW(Other.GetW());
	return *this;
}

Vector3& Vector3::operator=(Vector3&& Other) noexcept {
	if (this == &Other) return *this;
	SetX(Other.GetX());
	SetY(Other.GetY());
	SetZ(Other.GetZ());
	SetW(Other.GetW());
	return *this;
}

Vector3 Vector3::operator+(const Vector3& Other) const {
	return {this->GetX() + Other.GetX(), this->GetY() + Other.GetY(), this->GetZ() + Other.GetZ()};
}

Vector3& Vector3::operator+=(const Vector3& Other) {
	*this = *this + Other;
	return *this;
}

Vector3 Vector3::operator*(const double Other) const {
	return { GetX() * Other, GetY()*Other, GetZ()*Other };
}
Vector3& Vector3::operator*=(const double Other) {
	*this = *this * Other; return *this;
}

Vector3 Vector3::operator/(const double Other) const {
	auto _ = Vector3{GetX() / Other, GetY() / Other, GetZ() / Other};
	_.SetW(GetW()/ Other);
	return _;
}

double Vector3::GetX() const { return this->Position[0]; }
double Vector3::GetY() const { return this->Position[1]; }
double Vector3::GetZ() const { return this->Position[2]; }
Vector2 Vector3::GetXy() const { return {this->GetX(), this->GetY()};}

double Vector3::GetW() const { return this->Position[3]; }
void Vector3::SetW(const double NewW) { this->Position[3] = NewW; }

void Vector3::SetX(const double NewX) { this->Position[0] = NewX; }
void Vector3::SetY(const double NewY) { this->Position[1] = NewY; }
void Vector3::SetZ(const double NewZ) { this->Position[2] = NewZ; }

Vector3& Vector3::Translate(const Vector3& Other) {
	SetX(GetX() + Other.GetX());
	SetY(GetY() + Other.GetY());
	SetZ(GetZ() + Other.GetZ());

	return *this;
}

Vector3& Vector3::Scale(const double Multiplier) {
	SetX(GetX() * Multiplier);
	SetY(GetY() * Multiplier);
	SetZ(GetZ() * Multiplier);

	return *this;
}

Vector3& Vector3::Scale(const Vector3& Other) {
	SetX(GetX() * Other.GetX());
	SetY(GetY() * Other.GetY());
	SetZ(GetZ() * Other.GetZ());

	return *this;
}

Vector3& Vector3::Rotate(const Matrix4X4& Other) {
	*this = Other * *this;
	return *this;
}

std::string Vector3::ToString() const {
	return Stringf("Vector2 {[X: %f, Y: %f, Z: %f] Homogenous: %f}", GetX(), GetY(), GetZ(), GetW());
}
