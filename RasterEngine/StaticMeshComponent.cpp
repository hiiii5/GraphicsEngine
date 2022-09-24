#include "StaticMeshComponent.h"

#include "GEngine.h"
#include "BaseObject.h"

StaticMeshComponent::StaticMeshComponent(StaticMesh Mesh):
	Sm(std::move(Mesh)),
	Material(DEFAULT_SHADER) {}

StaticMeshComponent::StaticMeshComponent(BaseObject* const Parent, StaticMesh Mesh): Component(Parent),
																					 Sm(std::move(Mesh)),
																					 Material(DEFAULT_SHADER) {}

StaticMeshComponent::StaticMeshComponent(BaseObject* const Parent, StaticMesh Mesh, Mat4 WorldTransform):
	Component(Parent),
	Sm(std::move(Mesh)),
	WorldTransform(std::move(WorldTransform)),
	Material(DEFAULT_SHADER) {}

void StaticMeshComponent::Start() {
	
}

void StaticMeshComponent::Update() {
	
}

void StaticMeshComponent::Render() {
	RenderHelper::CurrentShader = &Material;
	if(RenderWire) {
		RenderHelper::DrawWireMesh(GEngine::Get()->MainCamera, GetParent()->WorldTransform, Sm.Vertices, Sm.Indices);
	}
	else {
		RenderHelper::FillMesh(GEngine::Get()->MainCamera, GetParent()->WorldTransform, Sm.Vertices, Sm.Indices, Sm.Uv);
	}

	RenderHelper::CurrentShader = nullptr;
}

void StaticMeshComponent::Destroy() {
	
}
