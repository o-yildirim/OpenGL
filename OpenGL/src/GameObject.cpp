#include <iostream>
#include "GameObject.h"

GameObject::~GameObject()
{
    for (Component* component : this->components)
    {
        delete component;
    }
    this->components.clear();
}
