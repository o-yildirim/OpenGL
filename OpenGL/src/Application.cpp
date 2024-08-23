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
        float positions[] = 
        {
           -50.0f, -50.0f, //0.0f, 0.0f,//index: 0,  (left bottom)
            50.0f, -50.0f, //1.0f, 0.0f, //1
            50.0f,  50.0f, //1.0f, 1.0f,//2 (top right)
           -50.0f,  50.0f //0.0f, 1.0f//3 
        };

        unsigned int indices[] = 
        {
            0,1,2,
            2,3,0
        };
    
        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        //layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 projection = glm::ortho(0.0f, (float)Window::GetWidth(), 0.0f, (float)Window::GetHeight(), -1.0f, 1.0f); //The first 4 values just adhere the 4:3 ratio, the values can be 2 * they are.
        glm::mat4 view = glm::mat4(1.0f); 
                                                                                         

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);


        GameObject square;
        square.AddComponent<Transform>();
        Transform* transform = square.GetComponent<Transform>();

      
        transform->Translate(Window::GetCenter());
        userInterface.SetTransform(transform);
        

        Renderer renderer;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            /* Render here */
            renderer.Clear();

            userInterface.NewFrame();
            userInterface.DrawTransformWindow();
            userInterface.EndFrame();
            
         
            transform->Update();
            glm::mat4 mvp = projection * view * transform->getModelMatrix();
           
            shader.Bind();
            shader.SetUniformMat4f("u_ModelViewProjection", mvp);
            renderer.Draw(va, ib, shader);
            

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