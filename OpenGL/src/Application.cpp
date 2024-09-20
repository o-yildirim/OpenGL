#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObject.h"
#include "Camera.h"


#include "EditorUI.h"
#include "ComponentUI.h"
#include "SceneUI.h"
#include "Window.h"
#include "Input.h"
#include "Picking.h"

#include "glm/glm.hpp"



void SetupSampleScene(Scene& sampleScene)
{


    GameObject* camera = new GameObject("Camera");
    camera->AddComponent<Camera>();
    sampleScene.AddObject(camera);

    GameObject* circle = new GameObject("Circle");
    circle->AddComponent<Circle>();
    circle->GetComponent<Transform>()->Translate(glm::vec3(Window::GetCenter().x - 200.0f, Window::GetCenter().y, 0.0f));
    sampleScene.AddObject(circle);

    GameObject* square = new GameObject("Square");
    square->AddComponent<Rectangle>();
    Transform* squareTransform = square->GetComponent<Transform>();
    squareTransform->Translate(glm::vec3(200.0f,0.0f, 0.0f));
    circle->AddChild(square);

    ComponentUI::SetGameObject(circle);

    

    /*
    circle->GetRoot();
    
    GameObject* empty = new GameObject("Empty_c_child");
    circle->AddChild(empty);
    
    empty->GetRoot();

    
    GameObject* empty2 = new GameObject("Empty2");
    sampleScene.AddObject(empty2);
    */
}

void calculateFpsAndDeltaTime(int* numFrames, double* currentFrame, double* lastFrame, double* lastTime, double* deltaTime)
{   
    (*numFrames)++;
    *currentFrame = glfwGetTime();
    *deltaTime = *currentFrame - *lastFrame;
    *lastFrame = *currentFrame;
    if (*currentFrame - *lastTime >= 1.0)
    {
        EditorUI::UpdateFramerate(*numFrames);
        *numFrames = 0;
        *lastTime = *currentFrame;
    }
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    Window::Init();
    window = glfwCreateWindow(Window::GetWidth(), Window::GetHeight(), "Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK) 
    {
        std::cout << "Error";
    }

   
    Input::Init(window);
    EditorUI::Init(window);
    Scene sampleScene("Sample Scene");
    SetupSampleScene(sampleScene);
    SceneUI::SetCurrentScene(&sampleScene);
    
    //BELOW MAIN PROGRAM.
    {

                               
        Shader wireframeShader("res/shaders/ColorlessBasic.shader");
        Shader coloredShader("res/shaders/Basic.shader");
        coloredShader.Bind();

        
        Renderer renderer;
        std::vector<GameObject*> traversedScene = sampleScene.TraverseDepthFirst();
        Camera* firstCam = nullptr;
        for (GameObject* obj : traversedScene)
        {
            firstCam = obj->GetComponent<Camera>();
            if (firstCam != nullptr) break;
        }
        
       

        Picking::SetCamera(firstCam);

        double currentFrame = glfwGetTime();
        double lastFrame = currentFrame;
        double deltaTime;

        int numFrames = 0;

        double lastTime = 0.0;
        
        while (!glfwWindowShouldClose(window))
        {
            calculateFpsAndDeltaTime(&numFrames, &currentFrame, &lastFrame, &lastTime, &deltaTime);
            //std::cout << Picking::GetSelectedObjects().size() << std::endl;
            Picking::Update(sampleScene.TraverseDepthFirst());
            

            if (Picking::GetSelectedObjects().size() == 1)
            {
                ComponentUI::SetGameObject(Picking::GetSelectedObjects()[0]);
            }
            

            renderer.Clear();

        
            
            

            if (firstCam != nullptr) 
            {
                //Render shapes.
                renderer.RenderScene(sampleScene, coloredShader, firstCam);

                //Render picked object wireframes.
                renderer.RenderPicking(wireframeShader, firstCam);
            }

           
            
            EditorUI::NewFrame();

            
            
            ComponentUI::DrawObjectComponents();
            ComponentUI::DrawAddComponentButton();

            SceneUI::DrawSceneTree();

            EditorUI::DisplayFrameRate();

            EditorUI::EndFrame();
            EditorUI::Render();
            Input::Update();
            


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }

    EditorUI::Terminate();
    glfwTerminate();
    return 0;
}