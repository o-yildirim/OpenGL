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

    GameObject* square = new GameObject("Square");
    square->AddComponent<Rectangle>();
    square->GetComponent<Transform>()->Translate(glm::vec3(Window::GetCenter().x - 200.0f, Window::GetCenter().y, 0.0f));
    sampleScene.AddObject(square);

    ComponentUI::SetGameObject(square);

    GameObject* circle = new GameObject("Circle");
    circle->AddComponent<Circle>();
    circle->GetComponent<Transform>()->Translate(glm::vec3(Window::GetCenter().x + 200.0f, Window::GetCenter().y, 0.0f));
    //sampleScene.AddObject(circle);

    square->AddChild(circle);
    GameObject* empty = new GameObject("Empty_c_child");
    circle->AddChild(empty);
    
    GameObject* empty2 = new GameObject("Empty2");
    sampleScene.AddObject(empty2);

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
      
        
        GameObject* camera = new GameObject("Camera");
        camera->AddComponent<Camera>();
        sampleScene.AddObject(camera);
                                

        Shader wireframeShader("res/shaders/ColorlessBasic.shader");

        Shader coloredShader("res/shaders/Basic.shader");
        coloredShader.Bind();
 

        /*
        GameObject square("Square");
        square.AddComponent<Rectangle>();
        square.GetComponent<Transform>()->Translate(glm::vec3(Window::GetCenter().x - 200.0f, Window::GetCenter().y, 0.0f));


        ComponentUI::SetGameObject(&square);
        
        GameObject circle("Circle");
        circle.AddComponent<Circle>();
        circle.GetComponent<Transform>()->Translate(glm::vec3(Window::GetCenter().x + 200.0f, Window::GetCenter().y, 0.0f));
     
        */

        
        Renderer renderer;
        Picking picking;
        picking.SetCamera(camera->GetComponent<Camera>());

        double currentFrame = glfwGetTime();
        double lastFrame = currentFrame;
        double deltaTime;

        int numFrames = 0;
        double lastTime = 0.0;
        
        while (!glfwWindowShouldClose(window))
        {
            numFrames++;
            currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            if (currentFrame - lastTime >= 1.0)
            {
                //std::cout << numFrames << std::endl;
                numFrames = 0;
                lastTime = currentFrame;
                
            }
            
            picking.Update(sampleScene.GetGameObjects());
            

            if (picking.GetSelectedObjects().size() == 1)
            {
                ComponentUI::SetGameObject(picking.GetSelectedObjects()[0]);
            }
            

            renderer.Clear();

        
            //Render shapes.
            coloredShader.Bind();
            for (GameObject* object : sampleScene.GetGameObjects())
            {
                Transform* transform = object->GetComponent<Transform>();
                if (transform == nullptr)
                {
                    std::cout << "NULL" << std::endl;
                }
                transform->Update();
                glm::mat4 mvp = camera->GetComponent<Camera>()->GetProjectionMatrix() * camera->GetComponent<Camera>()->GetViewMatrix() * transform->getModelMatrix();
                coloredShader.SetUniformMat4f("u_ModelViewProjection", mvp);
                renderer.Draw(*object, coloredShader);
            }
            

            //Render picked object wireframes.
            wireframeShader.Bind();
            //std::cout << picking.GetSelectedObjects().size() << std::endl;
            for (GameObject* pickedObject : picking.GetSelectedObjects())
            {
                Transform* transform = pickedObject->GetComponent<Transform>();
                if (transform == nullptr)
                {
                    std::cout << "NULL" << std::endl;
                }
                glm::mat4 mvp = camera->GetComponent<Camera>()->GetProjectionMatrix() * camera->GetComponent<Camera>()->GetViewMatrix() * transform->getModelMatrix();
                wireframeShader.SetUniformMat4f("u_ModelViewProjection", mvp);
                renderer.DrawWireframe(*pickedObject, wireframeShader);
            }
            
            EditorUI::NewFrame();
            
            //Display framerate TODO

            ComponentUI::DrawObjectComponents();
            ComponentUI::DrawAddComponentButton();

            SceneUI::DrawSceneTree();

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