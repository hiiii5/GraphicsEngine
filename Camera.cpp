#include "Camera.h"

#include "Matrix4x4.h"
#include "MathDefines.h"
#include "Vector3.h"

Vector2 Camera::ProjectOntoScreen(const Vector3& P, const Matrix4X4& PTransform) const {
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
	projected2D.SetX((projected2D.GetX() * 0.5f + 0.5f) * static_cast<float>(GetScreenWidth()));
	projected2D.SetY((1.0f - (projected2D.GetY() * 0.5f + 0.5f)) * static_cast<float>(GetScreenHeight()));
	
	// Return the screen space coordinate.
	return projected2D.GetXy();
}

Matrix4X4 Camera::GetPerspectiveProjection() const {
	const auto ratio = 1.0f * ScreenWidth / ScreenHeight;
	const auto yScale = std::cos(FieldOfView/2) / std::sin(FieldOfView/2);
	const auto xScale = yScale * ratio;

	const float _[16] = {
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
