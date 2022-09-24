#include "BaseObject.h"
#include "GEngine.h"
#include "Component.h"
#include "StaticMeshComponent.h"

BaseObject::BaseObject(): Id(-1) {
	GEngine::Get()->StartEvent.Subscribe(L"Test", [&]{ Start(); });
	GEngine::Get()->UpdateEvent.Subscribe(L"Test", [&]{ Update(); });
	GEngine::Get()->RenderEvent.Subscribe(L"Test", [&]{ Render(); });
	GEngine::Get()->DestroyEvent.Subscribe(L"Test", [&]{ Destroy(); });
}

BaseObject::~BaseObject() = default;

BaseObject::BaseObject(const BaseObject& Other) = default;

BaseObject::BaseObject(BaseObject&& Other) noexcept {
	this->Id = Other.Id;
}

BaseObject& BaseObject::operator=(const BaseObject& Other) {
	if (this == &Other) return *this;
	return *this;
}
BaseObject& BaseObject::operator=(BaseObject&& Other) noexcept {
	if (this == &Other) return *this;
	return *this;
}

void BaseObject::Start() {
	for (const auto& component : Components) {
		component->Start();
	}
}

void BaseObject::Update() {
	for (const auto& component : Components) {
		component->Update();
	}
}

void BaseObject::Render() {
	for (const auto& component : Components) {
		component->Render();
	}
}

void BaseObject::Destroy() {
	for (const auto& component : Components) {
		component->Destroy();
		delete component;
	}
	Components.clear();
}

int BaseObject::GetId() const {
	return Id;
}

void BaseObject::SetId(const int Id) {
	this->Id = Id;
}

Component* BaseObject::AddComponent(Component* C) {
	C->SetParent(this);

	Components.emplace_back(C);
	return Components.back();
}

Component* BaseObject::GetComponent(const unsigned Index) const {
	if(Index > Components.size()) { throw std::exception("Array out of bounds"); }

	return Components[Index];
}
