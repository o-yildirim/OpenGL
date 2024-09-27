#pragma once
#include "vector"
#include <iostream>
#include "Component.h"
#include "Transform.h"

class GameObject
{
private:
	std::vector<Component*> components;
	std::vector<GameObject*> _children;
	GameObject* parent = nullptr;
	std::string _name;
	bool disabled = false;
	

public:
	GameObject(std::string name);
	~GameObject();


	template<typename T>
	void AddComponent()
	{
		if (this->GetComponent<T>() == nullptr) //Cannot add the same component twice.
		{
			T* comp = new T();
			comp->SetGameObject(this);
			this->components.push_back(comp);
		}
		else
		{
			std::cout << "GameObject already has that component!" << std::endl;
		}
	}

	template<typename T>
	void AddComponent(T* component)
	{
		std::cout << "Will look for " << typeid(T).name() << " in GetComponent. "<< std::endl;
		if(this->GetComponent<T>() == nullptr) // Ensure no duplicate component type
		{
			component->SetGameObject(this);
			this->components.push_back(component);
		}
		else
		{
			std::cout << "GameObject already has "<< typeid(T).name() << std::endl;
			delete component;
		}
	}


	template<typename T>
	T* GetComponent()
	{

		for (int i = 0; i < this->components.size(); i++)
		{
			T* component = dynamic_cast<T*>(this->components[i]);
			if (component != nullptr)
			{
				return component; // Return the component if it matches type T
			}
		}
		return nullptr;
	}

	template<typename T>
	void RemoveComponent()
	{
		T* component = this->GetComponent<T>();
		if (component)
		{
			this->components.erase(std::remove(this->components.begin(), this->components.end(), component), this->components.end());
			std::cout << "Component removed!" << std::endl;
		}
	}

	inline std::vector<Component*> GetAllComponents() { return this->components; }
	inline const std::string GetName() const { return this->_name; }
	inline void SetName(std::string name) { this->_name = name; }

	inline const std::vector<GameObject*>& GetChildren() const { return this->_children; }
	inline GameObject* GetParent() const { return this->parent; }
	inline void SetParent(GameObject* parent) { this->parent = parent; }
	inline void SetDisabled(bool state) { this->disabled = state; }
	inline bool GetDisabled() const { return this->disabled; }
	
	void AddChild(GameObject* obj); 
	void RemoveChild(GameObject* obj); 
	bool IsChild(GameObject* obj); 
	
};