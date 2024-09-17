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

#include "ComponentUI.h"
#include "Window.h"
#include "Input.h"
#include "Picking.h"

#include "glm/glm.hpp"


/*
void SetupSampleScene(Scene* sampleScene)
{
    //TODO
}
*/

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
    ComponentUI::Init(window);
    //Scene sampleScene;
    //SetupSampleScene(&sampleScene);
    
    

    //BELOW MAIN PROGRAM.
    {
      

        GameObject camera;
        camera.AddComponent<Camera>();
                                    

        Shader wireframeShader("res/shaders/ColorlessBasic.shader");

        Shader coloredShader("res/shaders/Basic.shader");
        coloredShader.Bind();
 


        GameObject square;
        square.AddComponent<Rectangle>();
        square.GetComponent<Transform>()->Translate(glm::vec3(Window::GetCenter().x - 200.0f, Window::GetCenter().y, 0.0f));


        ComponentUI::SetGameObject(&square);
        
        GameObject circle;
        circle.AddComponent<Circle>();
        circle.GetComponent<Transform>()->Translate(glm::vec3(Window::GetCenter().x + 200.0f, Window::GetCenter().y, 0.0f));
     

        std::vector<GameObject*> objectsToRender;
        objectsToRender.push_back(&circle);
        objectsToRender.push_back(&square);

        
        Renderer renderer;
        Picking picking;
        picking.SetCamera(camera.GetComponent<Camera>());

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

           /* if (Input::GetKeyDown(Keys::Space))
            {
                circle.RemoveComponent<Circle>();
            }
            */
            
            picking.Update(objectsToRender);
            

            if (picking.GetSelectedObjects().size() == 1)
            {
                ComponentUI::SetGameObject(picking.GetSelectedObjects()[0]);
            }
            

            renderer.Clear();

            
            
          

            //Render shapes.
            coloredShader.Bind();
            for (GameObject* object : objectsToRender)
            {
                Transform* transform = object->GetComponent<Transform>();
                transform->Update();
                glm::mat4 mvp = camera.GetComponent<Camera>()->GetProjectionMatrix() * camera.GetComponent<Camera>()->GetViewMatrix() * transform->getModelMatrix();
                coloredShader.SetUniformMat4f("u_ModelViewProjection", mvp);
                renderer.Draw(*object, coloredShader);
            }
            

            //Render picked object wireframes.
            wireframeShader.Bind();
            //std::cout << picking.GetSelectedObjects().size() << std::endl;
            for (GameObject* pickedObject : picking.GetSelectedObjects())
            {
                Transform* transform = pickedObject->GetComponent<Transform>();
                glm::mat4 mvp = camera.GetComponent<Camera>()->GetProjectionMatrix() * camera.GetComponent<Camera>()->GetViewMatrix() * transform->getModelMatrix();
                wireframeShader.SetUniformMat4f("u_ModelViewProjection", mvp);
                renderer.DrawWireframe(*pickedObject, wireframeShader);
            }
            
            ComponentUI::NewFrame();
            ComponentUI::DrawObjectComponents();
            ComponentUI::DrawAddComponentButton();
            ComponentUI::EndFrame();
            ComponentUI::Render();
            Input::Update();
            


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }

    ComponentUI::Terminate();
    glfwTerminate();
    return 0;
}