#include "Scene.h"
#include "ComponentUtil.h"

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

void Scene::Save()
{
	
	nlohmann::json objectArray;
	for (GameObject* obj : this->GetGameObjects())
	{
		nlohmann::json objJson;
		obj->to_json(objJson);
		objectArray.push_back(objJson);
	}

	nlohmann::json sceneJson = nlohmann::json{
		   {"name", this->_name},
		   {"objects", objectArray}
	};

	std::string filePath = this->_name + ".json";
	std::ofstream file(filePath);
	if (file.is_open())
	{
		file << sceneJson.dump(4);
		file.close();
	}
	else {
		std::cerr << "Could not open the file for writing." << std::endl;
	}
}

void Scene::Load(std::string path)
{
	nlohmann::json jsonData;
	std::ifstream file(path);

	if (file.is_open()) 
	{
		file >> jsonData;
		file.close();
		//std::cout << jsonData.dump(4) << std::endl;  // Pretty-print with 4 spaces
	}

	Scene* loadedScene = new Scene(jsonData["name"]);
	

	nlohmann::json objects = jsonData["objects"];
	for (nlohmann::json object:objects)
	{
		GameObject* sceneObj = new GameObject(object["name"]);
		sceneObj->from_json(object);
		loadedScene->AddObject(sceneObj);
	}
	//After the entire scene is loaded.
	
	Picking::Reset();
	ComponentUI::SetGameObject(loadedScene->GetGameObjects()[0]);

	Scene* cur = SceneUI::GetCurrentScene();
	if (cur != nullptr && cur != loadedScene)
	{
		std::cout << "Deleting current scene" << std::endl;
		delete cur;
	}
	std::cout << "Setting the new scene" << std::endl;
	SceneUI::SetCurrentScene(loadedScene);
}