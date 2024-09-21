#include "ComponentUI.h"


GameObject* ComponentUI::_gameObjectToDisplay;

void ComponentUI::DrawObjectComponents()
{
    ImGui::SetNextWindowSize(ImVec2(360, Window::GetHeight()));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
    ImGui::Begin("Components");
    for (Component* component : _gameObjectToDisplay->GetAllComponents())
    {
        DrawComponent(component);
         
    }
    ImGui::PopStyleColor();

}

void ComponentUI::DrawComponent(Component* component)
{
    if (ImGui::CollapsingHeader(component->GetClassName(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (strcmp("Transform", component->GetClassName()) != 0)
        {
            float headerWidth = ImGui::GetContentRegionAvail().x;
            float buttonWidth = ImGui::CalcTextSize("...").x + 2 * ImGui::GetStyle().FramePadding.x;

            ImGui::SameLine(headerWidth - buttonWidth * 0.5f);
            std::string buttonId = "...##" + std::to_string(reinterpret_cast<uintptr_t>(component));
            if (ImGui::Button(buttonId.c_str()))
            {
                
                std::string popupId = "RemoveComponentDropdown_" + std::to_string(reinterpret_cast<uintptr_t>(component));
                //std::cout << "Button clicked on " << std::to_string(reinterpret_cast<uintptr_t>(component)) << std::endl;
                
                ImGui::OpenPopup(popupId.c_str());
            }          
        }     
        component->DisplayComponent();
        DisplayThreeDotsPopup(component);
        
    }
}

void ComponentUI::DisplayThreeDotsPopup(Component* component)
{
    const std::unordered_map<const char*, std::function<void()>> componentMap =
    {
        {"Circle", []() {_gameObjectToDisplay->RemoveComponent<Circle>(); }},
        {"Rectangle",[]() {_gameObjectToDisplay->RemoveComponent<Rectangle>(); }},
        {"Camera",[]() {_gameObjectToDisplay->RemoveComponent<Camera>(); }},
    };

    std::string popupId = "RemoveComponentDropdown_" + std::to_string(reinterpret_cast<uintptr_t>(component));
    
    if (ImGui::BeginPopup(popupId.c_str()))
    {
        //std::cout << "Popup started." << std::endl;
        if (ImGui::MenuItem("Remove Component"))
        {
            for (const auto& pair : componentMap)
            {
                if (strcmp(pair.first, component->GetClassName())==0)
                {
                    pair.second();
                    break;
                }

            }
        }
        ImGui::EndPopup();
    }
    
}

void ComponentUI::DrawAddComponentButton()
{
    float windowWidth = ImGui::GetWindowSize().x;
    float buttonWidth = 100.0f;
    float padding = 20.0f; //Button will be 20 pixels lower than the previous component.
    
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + padding);
    ImGui::SetCursorPosX((windowWidth - buttonWidth) / 2.0f); //Button will be centered on x.

    if (ImGui::Button("Add Component")) 
    {
        ImGui::OpenPopup("AddComponentDropdown");
    }
    DisplayComponentSelectionMenu();
}

void ComponentUI::DisplayComponentSelectionMenu()
{
    if (ImGui::BeginPopup("AddComponentDropdown"))
    {
        const std::unordered_map<const char*, std::function<void()>> componentMap =
        {
            {"Circle", [](){_gameObjectToDisplay->AddComponent<Circle>(); }},
            {"Rectangle",[](){_gameObjectToDisplay->AddComponent<Rectangle>(); }},
            {"Camera",[](){_gameObjectToDisplay->AddComponent<Camera>(); }},
        };

        for (const auto& pair : componentMap) 
        {
            if (ImGui::MenuItem(pair.first))
            {
                pair.second();
            }
            
        }
        ImGui::EndPopup();
    }
}

