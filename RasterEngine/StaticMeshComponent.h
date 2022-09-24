#pragma once
#include "Component.h"
#include "EngineDefines.h"
#include "Shader.h"
#include "StaticMesh.h"

class StaticMeshComponent :
    public Component
{
public:
	explicit StaticMeshComponent(StaticMesh Mesh);

	StaticMeshComponent(BaseObject* Parent, StaticMesh Mesh);

	StaticMeshComponent(BaseObject* Parent, StaticMesh Mesh, Mat4 WorldTransform);

	void Start() override;
	void Update() override;
	void Render() override;
	void Destroy() override;

	StaticMesh Sm;

	Mat4 WorldTransform;

	Shader Material;

	bool RenderWire;
};

