#include "SceneUI.h"
#include "Window.h"
#include "Transform.h"

Scene* SceneUI::_currentScene;
float SceneUI::_offset = 30.0f;

void SceneUI::DrawSceneTree()
{
	const std::vector<GameObject*>& objectsInScene = _currentScene->GetGameObjects();
    ImGui::SetNextWindowSize(ImVec2(360, Window::GetHeight()));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
    ImGui::Begin("Scene");

    if (ImGui::CollapsingHeader(_currentScene->GetName().c_str(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen))
    {
        for (GameObject* obj : objectsInScene)
        {
            DrawSceneObj(obj);
        }
    }
    
    ImGui::PopStyleColor();
    ImGui::End();
}

void SceneUI::DrawSceneObj(GameObject* obj)
{
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + _offset);
    std::string headerId = obj->GetName() + "##" + std::to_string(reinterpret_cast<uintptr_t>(obj));
    if (obj->GetChildren().size() == 0)
    {
        if (ImGui::Selectable(headerId.c_str()))
        {
            glm::vec3 objPos = obj->GetComponent<Transform>()->position;
            std::cout << std::to_string(reinterpret_cast<uintptr_t>(obj)) <<", pos: " << objPos.x << ", " << objPos.y << ", "<< objPos.z << std::endl;
            return;
        }
    }
    else
    {
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() - _offset);
        if (ImGui::CollapsingHeader(headerId.c_str(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen))
        {
            
            for (GameObject* child : obj->GetChildren())
            {
                DrawSceneObj(child);
            }
        }
    }

}


/*
void SceneUI::DrawSceneObj(GameObject* obj)
{
    std::string headerId = obj->GetName() + "##" + std::to_string(reinterpret_cast<uintptr_t>(obj));
    //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + _offset);
    if (obj->GetChildren().size() == 0)
    {
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + _offset);
        if (ImGui::Selectable(headerId.c_str()))
        {
            return;
        }
    }
    else
    {
       
        if (ImGui::CollapsingHeader(headerId.c_str(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + _offset);
            for (GameObject* child : obj->GetChildren())
            {
                DrawSceneObj(child);
            }
        }
    }
    
}*/

