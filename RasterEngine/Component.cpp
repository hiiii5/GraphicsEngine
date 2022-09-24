#include "Component.h"
#include "BaseObject.h"

Component::Component(): Parent(nullptr) {}
Component::Component(BaseObject* const Parent): Parent(Parent) {}

BaseObject* Component::GetParent() const {
	return Parent;
}

bool Component::HasParent() const {
	return (Parent != nullptr) ? true : false; 
}

void Component::SetParent(BaseObject* P) {
	delete Parent;
	Parent = P;
}

