#pragma once
#include "imgui/imgui.h"
#include <typeinfo>
#include <string>


class GameObject;


class Component 
{
protected:
	bool disabled = false;
	const char* _className;
	GameObject* parent;

public:
	virtual ~Component() = default; //Virtual destructor to make Component polymorphic. 
	virtual void DisplayComponent() {}
	inline GameObject* GetParent() const { return this->parent; }
	inline void SetParent(GameObject* parent) { this->parent = parent; }
	const inline char* GetClassName() { return this->_className; }
	
};