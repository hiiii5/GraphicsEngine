#include "Actor.h"
Actor::Actor() : LocalTransform(Matrix4X4{}.LoadIdentity()), Parent(nullptr) {}

void Actor::AddLocalPosition(const Vector3& Offset) { LocalTransform.Translate(Offset); }

void Actor::SetLocalPosition(const Vector3& Position) { LocalTransform.SetPosition(Position); }

void Actor::AddLocalScale(const Vector3& Scale) { LocalTransform.Scale(Scale); }

void Actor::SetLocalScale(const Vector3& Scale) { LocalTransform.SetScale(Scale); }

Actor* Actor::GetParent() const { return Parent; }

void Actor::SetParent(Actor* NewParent) { Parent = NewParent; }

Actor::Actor(Actor&& Other) noexcept: LocalTransform(std::move(Other.LocalTransform)),
									  Parent(Other.Parent) {}

Actor& Actor::operator=(const Actor& Other) {
	if (this == &Other) return *this;
	LocalTransform = Other.LocalTransform;
	Parent = Other.Parent;
	return *this;
}

Actor& Actor::operator=(Actor&& Other) noexcept {
	if (this == &Other) return *this;
	LocalTransform = std::move(Other.LocalTransform);
	Parent = Other.Parent;
	return *this;
}
