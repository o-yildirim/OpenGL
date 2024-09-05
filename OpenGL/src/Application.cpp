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

#include "UserInterface.h"
#include "Window.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Input.h"
#include "Picking.h"

#include "glm/glm.hpp"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;



    window = glfwCreateWindow(Window::GetWidth(), Window::GetHeight(), "Soy estupido", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK) 
    {
        std::cout << "Error";
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    Input input(window);
    UserInterface userInterface(window);

    //BELOW MAIN PROGRAM.
    {
      

        GameObject camera;
        camera.AddComponent<Camera>();
                                    

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
 


        GameObject square;
        square.AddComponent<Rectangle>();
        square.GetComponent<Transform>()->Translate(glm::vec3(Window::GetCenter().x - 200.0f, Window::GetCenter().y, 0.0f));


        userInterface.SetGameObject(&square);
        
        GameObject circle;
        circle.AddComponent<Circle>();
        circle.GetComponent<Transform>()->Translate(glm::vec3(Window::GetCenter().x + 200.0f, Window::GetCenter().y, 0.0f));
     

        std::vector<GameObject*> objectsToRender;
        objectsToRender.push_back(&circle);
        objectsToRender.push_back(&square);

        
        Renderer renderer;
        Picking picking;
        picking.SetCamera(camera.GetComponent<Camera>());

        while (!glfwWindowShouldClose(window))
        {
            picking.Update(objectsToRender);
            

            if (picking.GetSelectedObject())
            {
                userInterface.SetGameObject(picking.GetSelectedObject());
            }
            Input::Update();

            renderer.Clear();

            userInterface.NewFrame();
            userInterface.DrawObjectComponents();
            userInterface.EndFrame();
            

            for (GameObject* object : objectsToRender)
            {
                Transform* transform = object->GetComponent<Transform>();
                transform->Update();
                glm::mat4 mvp = camera.GetComponent<Camera>()->GetProjectionMatrix() * camera.GetComponent<Camera>()->GetViewMatrix() * transform->getModelMatrix();
                shader.Bind();
                shader.SetUniformMat4f("u_ModelViewProjection", mvp);
                renderer.Draw(*object, shader);
            }


            userInterface.Render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }

    userInterface.Terminate();
    glfwTerminate();
    return 0;
}