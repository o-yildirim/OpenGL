#include "UserInterface.h"

static const std::unordered_map<std::string, std::function<Component*()>> componentMap =
{
    {"Circle", []() -> Circle* { return new Circle(); }},
    {"Rectangle",[]() -> Rectangle* { return new Rectangle(); }},
    {"Camera", []() -> Camera* { return new Camera(); }},
};

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
        component->DisplayComponent();
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
        std::cout << "Button clicked." << std::endl;
        ImGui::OpenPopup("AddComponentDropdown");
    }
    DisplayComponentSelectionMenu();
}

void UserInterface::DisplayComponentSelectionMenu()
{
    //TODO HERE
    if (ImGui::BeginPopup("AddComponentDropdown"))
    {
        if (ImGui::MenuItem("Option 1")) {
            std::cout << "Option 1 selected!" << std::endl;
        }
        if (ImGui::MenuItem("Option 2")) {
            std::cout << "Option 2 selected!" << std::endl;
        }
        if (ImGui::MenuItem("Option 3")) {
            std::cout << "Option 3 selected!" << std::endl;
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