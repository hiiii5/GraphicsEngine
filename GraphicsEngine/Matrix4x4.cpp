#include "Matrix4x4.h"
#include <string>
#include "Vector3.h"
#include <cmath>

#include "DebugHelper.h"
#include "MathDefines.h"

Matrix4X4::Matrix4X4() : M{} {
	// copy the identity matrix into this new matrix.
	this->LoadIdentity();
}

Matrix4X4::Matrix4X4(const double NewM[16]) : M{} {
	// Copy the new matrix array into the old
	for (int i = 0; i < 16; ++i) { this->M[i] = NewM[i]; }
}

Matrix4X4::~Matrix4X4() = default;

Matrix4X4::Matrix4X4(const Matrix4X4& Other): M{} {
	// Copy others matrix data into this.
	*this = Matrix4X4(Other.M);
}

Matrix4X4& Matrix4X4::operator=(const Matrix4X4& Other) {
	if (this == &Other) return *this;
	for (int i = 0; i < 16; ++i) { M[i] = Other.M[i]; }
	return *this;
}

Matrix4X4& Matrix4X4::operator=(Matrix4X4&& Other) noexcept {
	if (this == &Other) return *this;
	for (int i = 0; i < 16; ++i) { M[i] = Other.M[i]; }
	return *this;
}

Matrix4X4 Matrix4X4::operator+(const Matrix4X4& Other) const {
	auto tmp = *this;

	for (int i = 0; i < 16; ++i) { tmp[i] = tmp[i] + Other.M[i]; }

	return tmp;
}

Matrix4X4& Matrix4X4::operator+=(const Matrix4X4& Other) {
	*this = *this + Other;
	return *this;
}

Matrix4X4 Matrix4X4::operator*(const Matrix4X4& Other) const {
	double tmp[16];

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

	return Matrix4X4(tmp);
}

Vector3 Matrix4X4::operator*(const Vector3& Other) const {
	Vector3 tmp{};

	tmp.SetX(this->M[0]*Other.GetX() + this->M[4]*Other.GetY() + this->M[8]*Other.GetZ() + this->M[12]*Other.GetW());
	tmp.SetY(this->M[1]*Other.GetX() + this->M[5]*Other.GetY() + this->M[9]*Other.GetZ() + this->M[13]*Other.GetW());
	tmp.SetZ(this->M[2]*Other.GetX() + this->M[6]*Other.GetY() + this->M[10]*Other.GetZ() + this->M[14]*Other.GetW());
	tmp.SetW(this->M[3]*Other.GetX() + this->M[7]*Other.GetY() + this->M[11]*Other.GetZ() + this->M[15]*Other.GetW());

	return tmp;
}

Matrix4X4& Matrix4X4::operator*=(const Matrix4X4& Other) {
	*this = *this * Other;
	return *this;
}

Matrix4X4& Matrix4X4::Transform(const Matrix4X4& Other) {
	*this = Other * *this;
	return *this;
}

Matrix4X4& Matrix4X4::Translate(const Vector3& Translation) {
	const double translationMatrix[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		Translation.GetX(), Translation.GetY(), Translation.GetZ(), 1
	};

	const auto m = Matrix4X4(translationMatrix);

	*this = m * *this;
	return *this;
}

Matrix4X4& Matrix4X4::Scale(const Vector3& Scale) {
	const auto scalingMatrix = Matrix4X4(new double[]{
		Scale.GetX(), 0, 0, 0,
		0, Scale.GetY(), 0, 0,
		0, 0, Scale.GetZ(), 0,
		0, 0, 0, 1
	});

	*this *= scalingMatrix;
	return *this;
}

Matrix4X4& Matrix4X4::Rotate(const Vector3& Rotation) {
	// Rotation at this point is in degrees not radians.
	// Compose the rotation matrices in order of Z, Y, X to get to the final rotation of this matrix.
	*this *= GetRotationZ(DEG2_RAD(Rotation.GetZ()));
	*this *= GetRotationY(DEG2_RAD(Rotation.GetY()));
	*this *= GetRotationX(DEG2_RAD(Rotation.GetX()));

	return *this;
}

Vector3 Matrix4X4::GetPosition() {
	return {
	this->M[12],
	this->M[13],
	this->M[14]
	};
}

Matrix4X4& Matrix4X4::SetPosition(const Vector3& Pos) {
	this->M[12] = Pos.GetX();
	this->M[13] = Pos.GetY();
	this->M[14] = Pos.GetZ();

	return *this;
}

Matrix4X4& Matrix4X4::SetScale(const Vector3& Scale) {
	this->M[0] = Scale.GetX();
	this->M[4] = Scale.GetY();
	this->M[8] = Scale.GetZ();

	return *this;
}

Matrix4X4 Matrix4X4::Transpose() const {
	Matrix4X4 m = *this;
	// Flip rows and cols.
	double tmp = 0.0;

	// Do nothing for identity coordinates. Interchange the outsides, and then come in to finish.
	tmp = m[1];
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

Matrix4X4 Matrix4X4::Inverse() const {
	Matrix4X4 result;

	double d12 = (this->M[8] * this->M[13] - this->M[12] * this->M[9]);
	double d13 = (this->M[8] * this->M[14] - this->M[12] * this->M[10]);
	double d23 = (this->M[9] * this->M[14] - this->M[13] * this->M[10]);
	double d24 = (this->M[9] * this->M[15] - this->M[13] * this->M[11]);
	double d34 = (this->M[10] * this->M[15] - this->M[14] * this->M[11]);
	double d41 = (this->M[11] * this->M[12] - this->M[15] * this->M[8]);

	double tmp[16];
	tmp[0] = (this->M[5] * d34 - this->M[6] * d24 + this->M[7] * d23);
	tmp[1] = -(this->M[4] * d34 + this->M[6] * d41 + this->M[7] * d13);
	tmp[2] = (this->M[4] * d24 + this->M[5] * d41 + this->M[7] * d12);
	tmp[3] = -(this->M[4] * d23 - this->M[5] * d13 + this->M[6] * d12);

	const double determinant = this->M[0] * tmp[0] + this->M[1] * tmp[1] + this->M[2] * tmp[2] + this->M[3] * tmp[
		3];
	if (determinant == 0.0) { result = Matrix4X4{}.LoadIdentity(); }
	else {
		const double inv_det = 1.0 / determinant;
		tmp[0] *= inv_det;
		tmp[1] *= inv_det;
		tmp[2] *= inv_det;
		tmp[3] *= inv_det;
		tmp[4] = -(this->M[1] * d34 - this->M[2] * d24 + this->M[3] * d23) * inv_det;
		tmp[5] = (this->M[0] * d34 + this->M[2] * d41 + this->M[3] * d13) * inv_det;
		tmp[6] = -(this->M[0] * d24 + this->M[1] * d41 + this->M[3] * d12) * inv_det;
		tmp[7] = (this->M[0] * d23 - this->M[1] * d13 + this->M[2] * d12) * inv_det;

		d12 = this->M[0] * this->M[5] - this->M[4] * this->M[1];
		d13 = this->M[0] * this->M[6] - this->M[4] * this->M[2];
		d23 = this->M[1] * this->M[6] - this->M[5] * this->M[2];
		d24 = this->M[1] * this->M[7] - this->M[5] * this->M[3];
		d34 = this->M[2] * this->M[7] - this->M[6] * this->M[3];
		d41 = this->M[3] * this->M[4] - this->M[7] * this->M[0];

		tmp[8] = (this->M[13] * d34 - this->M[14] * d24 + this->M[15] * d23) * inv_det;
		tmp[9] = -(this->M[12] * d34 + this->M[14] * d41 + this->M[15] * d13) * inv_det;
		tmp[10] = (this->M[12] * d24 + this->M[13] * d41 + this->M[15] * d12) * inv_det;
		tmp[11] = -(this->M[12] * d23 - this->M[13] * d13 + this->M[14] * d12) * inv_det;
		tmp[12] = -(this->M[9] * d34 - this->M[10] * d24 + this->M[11] * d23) * inv_det;
		tmp[13] = (this->M[8] * d34 + this->M[10] * d41 + this->M[11] * d13) * inv_det;
		tmp[14] = -(this->M[8] * d24 + this->M[9] * d41 + this->M[11] * d12) * inv_det;
		tmp[15] = (this->M[8] * d23 - this->M[9] * d13 + this->M[10] * d12) * inv_det;
		memcpy(result.M, tmp, 16 * sizeof(double));
	}

	return result.Transpose();
}

Matrix4X4& Matrix4X4::Invert() {
	*this = this->Inverse();
	return *this;
}

Matrix4X4& Matrix4X4::LoadIdentity() {
	constexpr double temp[16]{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	memcpy_s(this->M, sizeof *this->M * 16 , temp, sizeof temp);

	return *this;
}

Matrix4X4 Matrix4X4::GetRotationX(const double Radians) {
	double _[16] = {
		1, 0, 0, 0,
		0, std::cos(Radians), -std::sin(Radians), 0,
		0, std::sin(Radians), std::cos(Radians), 0,
		0, 0, 0, 1
	};

	return Matrix4X4(_);
}

Matrix4X4 Matrix4X4::GetRotationY(const double Radians) {
	double _[16] = {
		std::cos(Radians), 0, -std::sin(Radians), 0,
		0, 1, 0, 0,
		std::sin(Radians), 0, std::cos(Radians), 0,
		0, 0, 0, 1
	};

	return Matrix4X4(_);
}

Matrix4X4 Matrix4X4::GetRotationZ(const double Radians) {
	double _[16] = {
		std::cos(Radians), -std::sin(Radians), 0, 0,
		std::sin(Radians), std::cos(Radians), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return Matrix4X4(_);
}

std::string Matrix4X4::ToString() const {
	std::string ret = "Matrix4x4 {\n    ";
	for (int i = 0; i < 16; ++i) {
		if (i % 4 == 0 && i != 0) ret += "\n    ";

		ret += std::to_string(M[i]) + " ";
	}
	ret += "\n}";

	return ret;
}

double& Matrix4X4::operator[](const unsigned int Index) {
	if (Index > 15) { throw std::exception("Array out of bounds"); }

	return this->M[Index];
}

bool operator==(const Matrix4X4& Lhs, const Matrix4X4& Rhs) {
	return IS_RELATIVELY_EQUAL(Lhs.M[0], Rhs.M[0])
		&& IS_RELATIVELY_EQUAL(Lhs.M[1], Rhs.M[1])
		&& IS_RELATIVELY_EQUAL(Lhs.M[2], Rhs.M[2])
		&& IS_RELATIVELY_EQUAL(Lhs.M[3], Rhs.M[3])
		&& IS_RELATIVELY_EQUAL(Lhs.M[4], Rhs.M[4])
		&& IS_RELATIVELY_EQUAL(Lhs.M[5], Rhs.M[5])
		&& IS_RELATIVELY_EQUAL(Lhs.M[6], Rhs.M[6])
		&& IS_RELATIVELY_EQUAL(Lhs.M[7], Rhs.M[7])
		&& IS_RELATIVELY_EQUAL(Lhs.M[8], Rhs.M[8])
		&& IS_RELATIVELY_EQUAL(Lhs.M[9], Rhs.M[9])
		&& IS_RELATIVELY_EQUAL(Lhs.M[10], Rhs.M[10])
		&& IS_RELATIVELY_EQUAL(Lhs.M[11], Rhs.M[11])
		&& IS_RELATIVELY_EQUAL(Lhs.M[12], Rhs.M[12])
		&& IS_RELATIVELY_EQUAL(Lhs.M[13], Rhs.M[13])
		&& IS_RELATIVELY_EQUAL(Lhs.M[14], Rhs.M[14])
		&& IS_RELATIVELY_EQUAL(Lhs.M[15], Rhs.M[15]);
}

bool operator!=(const Matrix4X4& Lhs, const Matrix4X4& Rhs) { return !(Lhs == Rhs); }
