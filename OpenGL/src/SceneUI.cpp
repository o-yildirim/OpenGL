#include "SceneUI.h"


Scene* SceneUI::_currentScene;
float SceneUI::_offset = 30.0f;
std::unordered_map<GameObject*, bool> SceneUI::headers;

void SceneUI::DrawSceneTree()
{	
	if (_currentScene == nullptr) return;

	const std::vector<GameObject*>& objectsInScene = _currentScene->GetGameObjects();
	ImGui::SetNextWindowSize(ImVec2(360, Window::GetHeight()));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	ImGui::Begin("Scene");


	if (ImGui::CollapsingHeader(_currentScene->GetName().c_str(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(1, 0, 0, 0));
		float firstMargin = ImGui::GetCursorPosX() + _offset;
		for (GameObject* obj : objectsInScene)
		{
			DrawSceneObj(obj, firstMargin);
		}
		ImGui::PopStyleColor(2);
	}


	ImGui::PopStyleColor();
	ImGui::End();
}

void SceneUI::DrawSceneObj(GameObject* obj, float margin)
{
	ImGui::SetCursorPosX(margin);
	std::string headerId = obj->GetName() + "##" + std::to_string(reinterpret_cast<uintptr_t>(obj));



	if (obj->GetChildren().size() == 0)
	{
		if (ImGui::Selectable(headerId.c_str()))
		{
			ComponentUI::SetGameObject(obj);
		}
		if (ImGui::BeginDragDropSource())
		{
			obj->SetDisabled(true);
			ImGui::SetDragDropPayload("GAMEOBJECT", &obj, sizeof(GameObject*)); // Use a unique payload identifier
			ImGui::Text("Dragging %s", obj->GetName().c_str());
			ImGui::EndDragDropSource();
		}
	}
	else
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4 oldColor = style.Colors[ImGuiCol_Button];
		style.Colors[ImGuiCol_Button] = ImVec4(0, 0, 0, 0);
		if (headers.find(obj) != headers.end())
		{
			if (headers[obj])//If extended
			{
				if (ImGui::ArrowButton(std::string(headerId + "_arr_down").c_str(), ImGuiDir_Down))
				{
					headers[obj] = false;

				}
				ImGui::SameLine();
				if (ImGui::Selectable(headerId.c_str()))
				{
					ComponentUI::SetGameObject(obj);
				}
				if (ImGui::BeginDragDropSource())
				{
					obj->SetDisabled(true);
					ImGui::SetDragDropPayload("GAMEOBJECT", &obj, sizeof(GameObject*)); // Use a unique payload identifier
					ImGui::Text("Dragging %s", obj->GetName().c_str());
					ImGui::EndDragDropSource();
				}

				if (headers[obj])
				{
					style.Colors[ImGuiCol_Button] = oldColor;
					margin += _offset;
					for (GameObject* child : obj->GetChildren())
					{
						DrawSceneObj(child, margin);
					}
				}

			}
			else//If collapsed
			{
				if (ImGui::ArrowButton(std::string(headerId + "_arr_right").c_str(), ImGuiDir_Right))
				{
					headers[obj] = true;
				}
				ImGui::SameLine();
				if (ImGui::Selectable(headerId.c_str()))
				{
					ComponentUI::SetGameObject(obj);
				}
				if (ImGui::BeginDragDropSource())
				{
					obj->SetDisabled(true);
					ImGui::SetDragDropPayload("GAMEOBJECT", &obj, sizeof(GameObject*)); // Use a unique payload identifier
					ImGui::Text("Dragging %s", obj->GetName().c_str());
					ImGui::EndDragDropSource();
				}
			}
		}
		else
		{
			headers[obj] = true;

		}	
	}


	// Drop target
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT"))
		{
			GameObject* droppedObj = *(GameObject**)payload->Data;

			if (droppedObj != obj)
			{
				Transform* childTransform = droppedObj->GetComponent<Transform>();
				glm::mat4 oldWorldMatrix = childTransform->GetWorldModelMatrix();
			

				if (GameObject* oldParent = droppedObj->GetParent())
				{
					oldParent->RemoveChild(droppedObj);
				}
				obj->AddChild(droppedObj);
				droppedObj->SetParent(obj);
				droppedObj->SetDisabled(false);

				Transform* parentTransform = obj->GetComponent<Transform>();
				glm::mat4 parentWorldMatrix = parentTransform->GetWorldModelMatrix();

				// Compute the new local transformation matrix
				glm::mat4 newLocalMatrix = glm::inverse(parentWorldMatrix) * oldWorldMatrix;
				childTransform->SetLocalFromWorldMatrix(newLocalMatrix);


				childTransform->MarkDirty();
				_currentScene->RemoveObject(droppedObj, false);
			}

		}
		ImGui::EndDragDropTarget();
	}

}




