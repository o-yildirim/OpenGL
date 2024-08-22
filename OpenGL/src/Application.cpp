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

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define PI = 3.14159265

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Soy estupido", NULL, NULL);
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

    const char* glsl_version = "#version 460";
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

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

        GLCall(glEnable(GL_BLEND)); //Blending
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); //Blending
        

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        //layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f); //The first 4 values just adhere the 4:3 ratio, the values can be 2 * they are.
        glm::mat4 view = glm::mat4(1.0f); 
                                                                                         

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);
        

        //Comment out the following 3 lines along with the line in shader to draw a texture.
        //Texture texture("res/textures/Test.png");
        //texture.Bind();
        //shader.SetUniform1i("u_Texture", 0); //We bound our texture to 0 by sending no parameter to texture.Bind(). 
                                            // If we said texture.Bind(2), then we would use shader.SetUniform1i("u_Texture",2);



        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        glm::vec3 translation(960/2.0, 540/2.0, 0.0f);
        glm::vec3 rotation(0.0f, 0.0f, 0.0f);
        glm::vec3 scale(1.0f, 1.0f, 1.0f);

        float xPos_min = 0.0f, xPos_max = 960.0f;
        float yPos_min = 0.0f, yPos_max = 540.0f;
        float zPos_min = 0.0f, zPos_max = 0.0f;

        float rot_min = 0.0f, rot_max = 360.0f;

        float xScale_min = -10.0f, xScale_max = 10.0f;
        float yScale_min = -10.0f, yScale_max = 10.0f;
        float zScale_min = 1.0f, zScale_max = 1.0f;

        float slider_width = 80;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            /* Render here */
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {

                ImGui::Begin("Transform"); // Create a window called "Hello, world!" and append into it.
                //Position
                ImGui::Text("Position");
                ImGui::Text("X:");
                ImGui::SameLine();
                ImGui::PushItemWidth(slider_width);
                ImGui::SliderFloat("##posX", &translation.x, xPos_min, xPos_max);
                ImGui::SameLine();

                ImGui::Text("Y:");
                ImGui::SameLine();
                ImGui::SliderFloat("##posY", &translation.y, yPos_min, yPos_max);
                ImGui::SameLine();

                ImGui::Text("Z:");
                ImGui::SameLine();
                ImGui::SliderFloat("##posZ", &translation.z, zPos_min, zPos_max);

                //Rotation
                ImGui::Text("Rotation");
                ImGui::Text("X:");
                ImGui::SameLine();
                ImGui::PushItemWidth(slider_width);
                ImGui::SliderFloat("##rotX", &rotation.x, rot_min, rot_max);
                ImGui::SameLine();

                ImGui::Text("Y:");
                ImGui::SameLine();
                ImGui::SliderFloat("##rotY", &rotation.y, rot_min, rot_max);
                ImGui::SameLine();

                ImGui::Text("Z:");
                ImGui::SameLine();
                ImGui::SliderFloat("##rotZ", &rotation.z, rot_min, rot_max);

                //Scale
                ImGui::Text("Scale");
                ImGui::Text("X:");
                ImGui::SameLine();
                ImGui::PushItemWidth(slider_width);
                ImGui::SliderFloat("##scaleX", &scale.x, xScale_min, xScale_max);
                ImGui::SameLine();

                ImGui::Text("Y:");
                ImGui::SameLine();
                ImGui::SliderFloat("##scaleY", &scale.y, yScale_min, yScale_max);
                ImGui::SameLine();

                ImGui::Text("Z:");
                ImGui::SameLine();
                ImGui::SliderFloat("##scaleZ", &scale.z, zScale_min, zScale_max);

                ImGui::PopItemWidth();
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
     
                ImGui::End();
            }


            //The following part goes to the Update method of transform class.
            glm::mat4 model(1.0f);

            //Translate
            model = glm::translate(model, translation);

            //Rotate
            model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

            //Scale
            model = glm::scale(model, scale);
           
            glm::mat4 mvp = projection * view * model;
           
            shader.Bind();
            shader.SetUniformMat4f("u_ModelViewProjection", mvp);
            renderer.Draw(va, ib, shader);
            

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}