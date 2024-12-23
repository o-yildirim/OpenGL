#pragma once
#include<vector>

#include "GameObject.h"
#include "SceneUI.h"
#include <fstream>


class Scene 
{
private:
	std::vector<GameObject*> _objectsInTheScene;
	std::string _name;
	void TraverseDepthFirstHelper(GameObject* obj,std::vector<GameObject*>& vec);
public:
	Scene() {};
	Scene(std::string name): _name(name) {}
	~Scene()
	{
		std::cout << "Scene destructor called" << std::endl;
		for (GameObject* obj : this->_objectsInTheScene)
		{
			if (obj != nullptr)
			{
				delete obj;
			}
		}
		this->_objectsInTheScene.clear();
		std::cout << "Scene destructor finished" << std::endl;
	}
	inline const std::vector<GameObject*>& GetGameObjects() const { return this->_objectsInTheScene; }
	inline void AddObject(GameObject* obj) { this->_objectsInTheScene.push_back(obj); }
	inline void RemoveObject(GameObject* obj, bool permanently) 
	{ 
		auto it = std::remove(this->_objectsInTheScene.begin(), this->_objectsInTheScene.end(), obj);

		if (it != this->_objectsInTheScene.end()) 
		{
			this->_objectsInTheScene.erase(it, _objectsInTheScene.end());
		}
		if(permanently)
			delete obj; //This object no longer exists within the scene.
 
	}
	
	inline const std::string GetName() const { return this->_name; }
	inline  void SetName(std::string name) {this->_name = name; }

	std::vector<GameObject*> TraverseDepthFirst();

	void Save();
	static void Load(std::string path);
};

