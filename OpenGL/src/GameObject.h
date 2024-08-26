#pragma once
#include "vector"
#include <iostream>
#include "Component.h"

class GameObject
{
private:
	std::vector<Component*> components;

public:
	GameObject();
	~GameObject();


	template<typename T>
	void AddComponent()
	{
		if (this->GetComponent<T>() == nullptr) //Cannot add the same component twice.
			this->components.push_back(new T);
		else
			std::cout << "GameObject already has that component!" << std::endl;
	}



	template<typename T>
	T* GetComponent()
	{
		for (int i = 0; i < this->components.size(); i++)
		{
			T* component = dynamic_cast<T*>(this->components[i]); //Attempt to cast component[i] to T
			if (component != nullptr)
			{
				return component; // Return the component if it matches type T
			}
		}
		return nullptr;
	}

	inline std::vector<Component*> GetAllComponents() { return this->components; }

};