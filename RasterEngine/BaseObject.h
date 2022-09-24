/**
 * \author Dustin Roden
 * \date 08/24/22
 * \brief Base class for all engine objects.
 */

#pragma once
#include <vector>

#include "Component.h"
#include "EngineDefines.h"

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	BaseObject(const BaseObject& Other);
	BaseObject(BaseObject&& Other) noexcept;

	BaseObject& operator=(const BaseObject& Other);

	BaseObject& operator=(BaseObject&& Other) noexcept;

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

	int GetId() const;
	void SetId(int Id);

	Component* AddComponent(Component* C);
	Component* GetComponent(unsigned Index) const;

	Mat4 WorldTransform;

private:
	int Id;

	std::vector<Component*> Components;
};



