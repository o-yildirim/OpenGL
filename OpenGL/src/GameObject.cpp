#include <iostream>
#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject()
{
    this->AddComponent<Transform>();
    this->GetComponent<Transform>()->SetParent(this);
}

GameObject::~GameObject()
{
    for (Component* component : this->components)
    {
        delete component;
    }
    this->components.clear();
}
