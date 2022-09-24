#pragma once
class BaseObject;

class Component
{
public:
	virtual ~Component() = default;
	Component();

	explicit Component(BaseObject* const Parent);

	BaseObject* GetParent() const;
	bool HasParent() const;
	void SetParent(BaseObject* P);

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

private:
	BaseObject* Parent;
};

