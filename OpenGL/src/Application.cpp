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

#include "UserInterface.h"
#include "Window.h"
#include "Rectangle.h"
#include "Circle.h"

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
    
    if (glewInit() != GLEW_OK) {
        std::cout << "Error";
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    UserInterface userInterface(window);

    //BELOW MAIN PROGRAM.
    {
      

        glm::mat4 projection = glm::ortho(0.0f, (float)Window::GetWidth(), 0.0f, (float)Window::GetHeight(), -1.0f, 1.0f); //The first 4 values just adhere the 4:3 ratio, the values can be 2 * they are.
        glm::mat4 view = glm::mat4(1.0f); 
                                                                               

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);


        GameObject square;
        userInterface.SetGameObject(&square);
        //square.AddComponent<Rectangle>();
        square.AddComponent<Circle>();

        Transform* transform = square.GetComponent<Transform>();
        
        
  
        Renderer renderer;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            /* Render here */
            renderer.Clear();

            userInterface.NewFrame();
            userInterface.DrawObjectComponents();
            userInterface.EndFrame();
            
         
            transform->Update();
            glm::mat4 mvp = projection * view * transform->getModelMatrix();
           
            shader.Bind();
            shader.SetUniformMat4f("u_ModelViewProjection", mvp);
            renderer.Draw(square, shader);

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