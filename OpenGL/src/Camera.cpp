#include "Camera.h"
#include "glm/glm.hpp"
#include <iostream>

Camera::Camera()
{
    this->_className = "Camera";
	this->_projectionMatrix = glm::ortho(0.0f, (float) Window::GetWidth(), 0.0f, (float)Window::GetHeight(), -1.0f, 1.0f); //The first 4 values just adhere the 4:3 ratio, the values can be 2 * they are.
	this->_viewMatrix = glm::mat4(1.0f);
}

glm::vec3 Camera::ConvertScreenToWorld(glm::vec3 pos)
{
    //std::cout << "Window width: " << Window::GetWidth() << ", Window height: " << Window::GetHeight() << std::endl;


    float x = (2.0f * pos.x) / Window::GetWidth() - 1.0f;
    float y = 1.0f - (2.0f * pos.y) / Window::GetHeight();  // Invert y-axis
    glm::vec2 normalizedPos(x, y);


    glm::vec4 clipCoords(normalizedPos.x, normalizedPos.y, -1.0f, 1.0f);
    glm::mat4 invVP = glm::inverse(this->_projectionMatrix * this->_viewMatrix);
    glm::vec4 worldCoords = invVP * clipCoords;

    // Normalize to get the world position (divide by w)
    glm::vec3 worldPosition = glm::vec3(worldCoords) / worldCoords.w;

    return worldPosition;
}

void Camera::to_json(nlohmann::json& j)
{
    nlohmann::json projectionMatrixJson;
    nlohmann::json viewMatrixJson;

    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            projectionMatrixJson["row" + std::to_string(i + 1)]["col" + std::to_string(j + 1)] = this->_projectionMatrix[i][j];
            viewMatrixJson["row" + std::to_string(i + 1)]["col" + std::to_string(j + 1)] = this->_viewMatrix[i][j];
        }
    }


    j = {
        {this->GetClassName(), {
            {"Projection Matrix", projectionMatrixJson},
            {"View Matrix", viewMatrixJson}
        }}
    };
};


void Camera::from_json(nlohmann::json& j) 
{

    nlohmann::json projectionMatrixJson = j.at("Projection Matrix");
    nlohmann::json viewMatrixJson = j.at("View Matrix");

    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 4; ++j) 
        {
            this->_projectionMatrix[i][j] = projectionMatrixJson["row" + std::to_string(i + 1)]["col" + std::to_string(j + 1)].get<float>();
            this->_viewMatrix[i][j] = viewMatrixJson["row" + std::to_string(i + 1)]["col" + std::to_string(j + 1)].get<float>();
        }
    }
};
