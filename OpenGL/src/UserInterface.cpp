#include "UserInterface.h"



UserInterface::UserInterface(GLFWwindow* window)
{
    this->window = window;
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init(this->glsl_version);
}

void UserInterface::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UserInterface::DrawObjectComponents()
{
    ImGui::Begin("Components");
    for (Component* component : this->gameObjectToDisplay->GetAllComponents())
    {
        this->DrawComponent(component);
         
    }
}

void UserInterface::DrawComponent(Component* component)
{
    if (ImGui::CollapsingHeader(component->GetClassName(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (strcmp("Transform", component->GetClassName()) != 0)
        {
        
            ImGui::SameLine();
            if (ImGui::Button("..."))
            {
                std::string popupId = "RemoveComponentDropdown_" + std::string(component->GetClassName());
                ImGui::OpenPopup(popupId.c_str());

            }
            this->DisplayThreeDotsPopup(component);
        }
        
        component->DisplayComponent();
        
    }
}

void UserInterface::DisplayThreeDotsPopup(Component* component)
{
    const std::unordered_map<const char*, std::function<void()>> componentMap =
    {
        {"Circle", [this]() {this->gameObjectToDisplay->RemoveComponent<Circle>(); }},
        {"Rectangle",[this]() {this->gameObjectToDisplay->RemoveComponent<Rectangle>(); }},
        {"Camera",[this]() {this->gameObjectToDisplay->RemoveComponent<Camera>(); }},
    };

    std::string popupId = "RemoveComponentDropdown_" + std::string(component->GetClassName());
    if (ImGui::BeginPopup(popupId.c_str()))
    {
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

void UserInterface::DrawAddComponentButton()
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

void UserInterface::DisplayComponentSelectionMenu()
{
    if (ImGui::BeginPopup("AddComponentDropdown"))
    {
        const std::unordered_map<const char*, std::function<void()>> componentMap =
        {
            {"Circle", [this](){this->gameObjectToDisplay->AddComponent<Circle>(); }},
            {"Rectangle",[this](){this->gameObjectToDisplay->AddComponent<Rectangle>(); }},
            {"Camera",[this](){this->gameObjectToDisplay->AddComponent<Camera>(); }},
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

void UserInterface::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::Terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UserInterface::EndFrame()
{
    ImGui::End();
}