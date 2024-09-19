#include "Scene.h"

void Scene::TraverseDepthFirstHelper(GameObject* obj,std::vector<GameObject*>& vec)
{
	vec.push_back(obj);

	for (GameObject* child : obj->GetChildren())
	{
		this->TraverseDepthFirstHelper(child,vec);
	}

}

std::vector<GameObject*> Scene::TraverseDepthFirst()
{
	std::vector<GameObject*> objects;
	for (GameObject* obj : this->GetGameObjects())
	{
		this->TraverseDepthFirstHelper(obj,objects);
	}
	return objects;
}