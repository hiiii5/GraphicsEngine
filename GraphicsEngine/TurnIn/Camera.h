#pragma once
#include "Actor.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"

class Camera : public Actor {
public:
	Camera(const double NearPlane, const double FarPlane, const uint32_t ScreenWidth, const uint32_t ScreenHeight,
		   const double FieldOfView)
		: NearPlane(NearPlane),
		  FarPlane(FarPlane),
		  ScreenWidth(ScreenWidth),
		  ScreenHeight(ScreenHeight),
		  FieldOfView(FieldOfView),
		  WorldTransform(Matrix4X4{}) {}

	double GetNearPlane() const { return NearPlane; }
	void SetNearPlane(const double NearPlane) { this->NearPlane = NearPlane; }
	double GetFarPlane() const { return FarPlane; }
	void SetFarPlane(const double FarPlane) { this->FarPlane = FarPlane; }
	uint32_t GetScreenWidth() const { return ScreenWidth; }
	void SetScreenWidth(const uint32_t ScreenWidth) { this->ScreenWidth = ScreenWidth; }
	uint32_t GetScreenHeight() const { return ScreenHeight; }
	void SetScreenHeight(const uint32_t ScreenHeight) { this->ScreenHeight = ScreenHeight; }
	double GetFieldOfView() const { return FieldOfView; }
	void SetFieldOfView(const double FieldOfView) { this->FieldOfView = FieldOfView; }
	Matrix4X4 GetWorldTransform() const { return WorldTransform; }
	void SetWorldTransform(const Matrix4X4& WorldTransform) { this->WorldTransform = WorldTransform; }

private:
	double NearPlane, FarPlane;
	uint32_t ScreenWidth, ScreenHeight;
	double FieldOfView;

	Matrix4X4 WorldTransform;

public:
	/** Projects a 3d point onto a 2d screen. */
	//Vector2 ProjectOntoScreen(const Vector3& P, const Matrix4X4& PTransform = Matrix4X4{}) const;

	Vector2 ProjectOntoScreen2(const Vector3& P, const Matrix4X4& PTransform = Matrix4X4{}) const;

	/** Calculates the current perspective project matrix. */
	Matrix4X4 GetPerspectiveProjection() const;

	/** Returns the inverse of the cameras world transform matrix.*/
	Matrix4X4 GetViewMatrix() const;
};
