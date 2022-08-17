#pragma once
class BaseObject {
public:
	BaseObject() = default;
	virtual ~BaseObject() = default;

	BaseObject(const BaseObject& Other) = default;
	BaseObject(BaseObject&& Other) noexcept {}

	BaseObject& operator=(const BaseObject& Other) {
		if (this == &Other) return *this;
		return *this;
	}

	BaseObject& operator=(BaseObject&& Other) noexcept {
		if (this == &Other) return *this;
		return *this;
	}

};
