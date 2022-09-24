#pragma once
#include "BaseObject.h"
#include "Shader.h"

class Actor :
    public BaseObject
{
public:
	void Start() override;
	void Update() override;
	void Render() override;
	void Destroy() override;
};

