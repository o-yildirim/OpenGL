#pragma once
#include "imgui/imgui.h"
class GameObject;

class Component 
{
protected:
	bool disabled = false;
	GameObject* parent;

public:
	virtual ~Component() = default; //Virtual destructor to make Component polymorphic. 
	virtual void DisplayComponent() {}
	inline GameObject* GetParent() const { return this->parent; }
	inline void SetParent(GameObject* parent) { this->parent = parent; }
};