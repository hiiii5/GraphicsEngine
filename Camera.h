#pragma once
#include "Actor.h"
#include "Matrix4x4.h"
#include "Vector2.h"

class Camera : public Actor {
public:
	Camera(const float NearPlane, const float FarPlane, const uint32_t ScreenWidth, const uint32_t ScreenHeight,
		   const float FieldOfView)
		: NearPlane(NearPlane),
		  FarPlane(FarPlane),
		  ScreenWidth(ScreenWidth),
		  ScreenHeight(ScreenHeight),
		  FieldOfView(FieldOfView),
		  WorldTransform(Matrix4X4{}) {}

	float GetNearPlane() const { return NearPlane; }
	void SetNearPlane(const float NearPlane) { this->NearPlane = NearPlane; }
	float GetFarPlane() const { return FarPlane; }
	void SetFarPlane(const float FarPlane) { this->FarPlane = FarPlane; }
	uint32_t GetScreenWidth() const { return ScreenWidth; }
	void SetScreenWidth(const uint32_t ScreenWidth) { this->ScreenWidth = ScreenWidth; }
	uint32_t GetScreenHeight() const { return ScreenHeight; }
	void SetScreenHeight(const uint32_t ScreenHeight) { this->ScreenHeight = ScreenHeight; }
	float GetFieldOfView() const { return FieldOfView; }
	void SetFieldOfView(const float FieldOfView) { this->FieldOfView = FieldOfView; }
	Matrix4X4 GetWorldTransform() const { return WorldTransform; }
	void SetWorldTransform(const Matrix4X4& WorldTransform) { this->WorldTransform = WorldTransform; }

private:
	float NearPlane, FarPlane;
	uint32_t ScreenWidth, ScreenHeight;
	float FieldOfView;

	Matrix4X4 WorldTransform;

public:
	/** Projects a 3d point onto a 2d screen. */
	//Vector2 ProjectOntoScreen(const Vector3& P, const Matrix4X4& PTransform = Matrix4X4{}) const;

	Vector2 ProjectOntoScreen(const Vector3& P, const Matrix4X4& PTransform = Matrix4X4{}) const;

	/** Calculates the current perspective project matrix. */
	Matrix4X4 GetPerspectiveProjection() const;

	/** Returns the inverse of the cameras world transform matrix.*/
	Matrix4X4 GetViewMatrix() const;
};
