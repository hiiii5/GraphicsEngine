#include "Camera.h"

#include "Matrix4x4.h"
#include "MathDefines.h"
#include "Vector3.h"

Vector2 Camera::ProjectOntoScreen2(const Vector3& P, const Matrix4X4& PTransform) const {
	// Rotate the parent object.
	Vector3 rotated = PTransform * P;

	rotated = GetViewMatrix() * rotated;

	// Perform perspective projection.
	Vector3 projected2D = GetPerspectiveProjection() * rotated;

	// Perform perspective divide. Take ndc space to screen space.
	projected2D = projected2D / projected2D.GetW();

	// Get the screen center.
	const auto halfWidth = 1.0 * GetScreenWidth() / 2.0;
	const auto halfHeight = 1.0 * GetScreenHeight() / 2.0;

	// Take view space to ndc space
	//projected2D.SetX(halfWidth * projected2D.GetX() + (P.GetX() + halfWidth));
	//projected2D.SetY(halfHeight * projected2D.GetY() + (P.GetY() + halfHeight));
	projected2D.SetX((projected2D.GetX() * 0.5 + 0.5) * GetScreenWidth());
	projected2D.SetY((1.0 - (projected2D.GetY() * 0.5 + 0.5)) * GetScreenHeight());
	
	// Return the screen space coordinate.
	return projected2D.GetXy();
}

//Vector2 Camera::ProjectOntoScreen2(const Vector3& P, const Matrix4X4& PTransform) const {
//	// Rotate the parent object.
//	//Vector3 rotated = PTransform * P;
//	const auto projection = GetPerspectiveProjection();
//	const auto modelView = PTransform * GetViewMatrix();
//	const auto mvp = modelView * projection;
//
//	// Get the screen center.
//	/*const auto halfWidth = 1.0 * GetScreenWidth() / 2.0;
//	const auto halfHeight = 1.0 * GetScreenHeight() / 2.0;*/
//
//	// Take camera space to screen space.
//	const auto ndcX = NearPlane * P.GetX() / -P.GetZ();
//	const auto ndcY = NearPlane * P.GetY() / -P.GetZ();
//
//	// Convert to camera space.
//	//const auto ndc = GetViewMatrix() * rotated;
//
//	// Perform perspective projection.
//	//Vector3 projected2D =  * rotated;
//
//	// Get the screen center.
//	const auto halfWidth = 1.0 * GetScreenWidth() / 2.0;
//	const auto halfHeight = 1.0 * GetScreenHeight() / 2.0;
//	Vector3 ret{};
//	ret.SetX(halfWidth * ndcX + (P.GetX() + halfWidth));
//	ret.SetY(halfHeight * ndcY + (P.GetX() + halfHeight));
//	//	projected2D.SetY(halfHeight * projected2D.GetY() + (P.GetX() + halfHeight));	
//
//	// Take ndc space to screen space
//	ret.SetX(halfWidth * ret.GetX() + (P.GetX() + halfWidth));
//	ret.SetY(halfHeight * ret.GetY() + (P.GetX() + halfHeight));
//
//	// Return the screen space coordinate.
//	return ret.GetXy();
//}

Matrix4X4 Camera::GetPerspectiveProjection() const {
	const auto ratio = 1.0 * ScreenWidth / ScreenHeight;
	const auto yScale = std::cos(FieldOfView/2) / std::sin(FieldOfView/2);
	const auto xScale = yScale * ratio;

	const double _[16] = {
		xScale, 0, 0, 0,
		0, yScale, 0, 0,
		0, 0, FarPlane / (FarPlane - NearPlane), 1,
		0, 0, -(FarPlane * NearPlane) / (FarPlane - NearPlane), 0
	};

	//printf("Projection Matrix: %s", _.ToString().c_str());

	return Matrix4X4(_);
}

Matrix4X4 Camera::GetViewMatrix() const {
	const auto _ = this->GetWorldTransform().Inverse();
	//printf("%s", _.ToString().c_str());
	return _;
}
