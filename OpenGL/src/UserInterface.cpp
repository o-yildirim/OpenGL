#include "UserInterface.h"


UserInterface::UserInterface(GLFWwindow* window)
{

    this->window = window;
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init(this->glsl_version);
}

void UserInterface::Init()
{

}

void UserInterface::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UserInterface::DrawTransformWindow()
{
    float xPos_min = 0.0f, xPos_max = 960.0f;
    float yPos_min = 0.0f, yPos_max = 540.0f;
    float zPos_min = 0.0f, zPos_max = 0.0f;

    float rot_min = 0.0f, rot_max = 360.0f;

    float xScale_min = -10.0f, xScale_max = 10.0f;
    float yScale_min = -10.0f, yScale_max = 10.0f;
    float zScale_min = 1.0f, zScale_max = 1.0f;
    float slider_width = 80;


    ImGui::Begin("Transform");
    //Position
    ImGui::Text("Position");
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::PushItemWidth(slider_width);
    ImGui::SliderFloat("##posX", &this->transformToDisplay->position.x, xPos_min, xPos_max);
    ImGui::SameLine();

    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::SliderFloat("##posY", &this->transformToDisplay->position.y, yPos_min, yPos_max);
    ImGui::SameLine();

    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::SliderFloat("##posZ", &this->transformToDisplay->position.z, zPos_min, zPos_max);

    //Rotation
    ImGui::Text("Rotation");
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::PushItemWidth(slider_width);
    ImGui::SliderFloat("##rotX", &this->transformToDisplay->rotation.x, rot_min, rot_max);
    ImGui::SameLine();

    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::SliderFloat("##rotY", &this->transformToDisplay->rotation.y, rot_min, rot_max);
    ImGui::SameLine();

    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::SliderFloat("##rotZ", &this->transformToDisplay->rotation.z, rot_min, rot_max);

    //Scale
    ImGui::Text("Scale");
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::PushItemWidth(slider_width);
    ImGui::SliderFloat("##scaleX", &this->transformToDisplay->scale.x, xScale_min, xScale_max);
    ImGui::SameLine();

    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::SliderFloat("##scaleY", &this->transformToDisplay->scale.y, yScale_min, yScale_max);
    ImGui::SameLine();

    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::SliderFloat("##scaleZ", &this->transformToDisplay->scale.z, zScale_min, zScale_max);

    ImGui::PopItemWidth();
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