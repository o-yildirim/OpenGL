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
    //std::cout << "Deleting " << this->GetName() << std::endl;
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

void GameObject::to_json(nlohmann::json& j) 
{
    nlohmann::json childArray = nlohmann::json::array();
    for (GameObject* child : this->GetChildren()) 
    {
        nlohmann::json childJson;
        child->to_json(childJson);
        childArray.push_back(childJson);
    }

    nlohmann::json componentArray = nlohmann::json::array();;
    for (const auto& component : this->GetAllComponents()) 
    {
        nlohmann::json compJson;
        component->to_json(compJson);
        if(compJson != nullptr)
            componentArray.push_back(compJson);
    }


    j = nlohmann::json{
           {"name", this->_name},
           {"components",componentArray},
           {"children", childArray}
    };

}

void GameObject::from_json(nlohmann::json& j)
{
    nlohmann::json components = j["components"];
    for (nlohmann::json component : components)
    {
        for (auto it = component.begin(); it != component.end(); ++it)
        {
            std::string key = it.key();
            if (key == "Transform")
            {
                Transform* comp = this->GetComponent<Transform>();
                comp->from_json(component[key]);
            }
            else if (key == "Camera")
            {
                Camera* comp = new Camera();
                comp->from_json(component[key]);
                this->AddComponent(comp);
            }
            else if (key == "Circle")
            {
                Circle* comp = new Circle();
                comp->from_json(component[key]);
                this->AddComponent(comp);
            }
            else if (key == "Rectangle")
            {
                Rectangle* comp = new Rectangle();
                comp->from_json(component[key]);
                this->AddComponent(comp);
            }
        }
    }

    nlohmann::json childrenJson = j["children"];
    for (nlohmann::json childjson : childrenJson)
    {
        GameObject* child = new GameObject(childjson["name"]);
        this->AddChild(child);
        child->from_json(childjson);
    }

}

