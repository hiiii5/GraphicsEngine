#pragma once
#include "BaseObject.h"
#include "Matrix4x4.h"

class Actor : public BaseObject {
public:
	Actor();
	~Actor() override = default;

	void AddLocalPosition(const Vector3& Offset);
	void SetLocalPosition(const Vector3& Position);

	void AddLocalScale(const Vector3& Scale);
	void SetLocalScale(const Vector3& Scale);

	Actor* GetParent() const;
	void SetParent(Actor* NewParent);

	Actor(const Actor& Other) = default;
	Actor(Actor&& Other) noexcept;

	Actor& operator=(const Actor& Other);
	Actor& operator=(Actor&& Other) noexcept;

private:
	Matrix4X4 LocalTransform;
	Actor* Parent;
};
