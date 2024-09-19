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
	GameObject* _gameObject;

public:
	virtual ~Component() = default; //Virtual destructor to make Component polymorphic. 
	virtual void DisplayComponent() {}
	inline GameObject* GetGameObject() const { return this->_gameObject; }
	inline void SetGameObject(GameObject* parent) { this->_gameObject = parent; }
	const inline char* GetClassName() { return this->_className; }
	
};