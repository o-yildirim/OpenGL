#include <iostream>
#include "GameObject.h"


GameObject::GameObject(std::string name)
    :_name(name)
{
    this->AddComponent<Transform>();
    this->GetComponent<Transform>()->SetGameObject(this);
}

GameObject::~GameObject()
{
    for (Component* component : this->components)
    {
        delete component;
    }
    this->components.clear();
}

void GameObject::AddChild(GameObject* obj)
{
    if (!this->IsChild(obj))
    {
        this->_children.push_back(obj);
        obj->parent = this;
    }

}

void GameObject::RemoveChild(GameObject* obj)
{
    auto it = std::remove(this->_children.begin(), this->_children.end(), obj);

    if (it != this->_children.end())
    {
        this->_children.erase(it, _children.end());
        obj->parent = nullptr;
    }
}

bool GameObject::IsChild(GameObject* obj)
{
    auto it = std::remove(this->_children.begin(), this->_children.end(), obj);

    if (it != this->_children.end()) 
    {
        return true;
    }
    return false;
}

