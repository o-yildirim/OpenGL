#include "Shader.h"
#include "Renderer.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>

Shader::Shader(const std::string& filepath)
{
	this->m_FilePath = filepath;
    ShaderProgramSource source = this->ParseShader(this->m_FilePath);
    this->m_RendererID = this->CreateShader(source.VertexSource,source.FragmentSource);
    
}

Shader::~Shader()
{
    glDeleteProgram(this->m_RendererID);
}



ShaderProgramSource Shader::ParseShader(const std::string filePath) 
{
    std::ifstream stream(filePath);
    if (!stream.is_open())
    {
        std::cout << "File could not be opened!" << std::endl;
    }


    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::string line;
    std::string vertexSource = "";
    std::string fragmentSource = "";
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos) //npos means it hasn't found it.
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            if (type == ShaderType::VERTEX)
            {
                vertexSource.append(line + '\n');
            }
            else if (type == ShaderType::FRAGMENT)
            {
                fragmentSource.append(line + '\n');
            }
        }
    }


    return ShaderProgramSource{ vertexSource, fragmentSource };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) 
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    //For glShaderSource(...)
    //Count: specifying only 1 source code.
    //There is a double pointer for src.
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //Error handling below.
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); //iv: integer and vector. We are querying the shader status  to see if it is okay and there is no error.
    if (result == GL_FALSE) //Shader is not compiled successfully. 
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        delete[] message;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
{
    //The parameter strings are the source codes of the shaders.
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    //Shaders are already stored in the program now, so we can delete them from here.
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const
{
    glUseProgram(this->m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);

}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(this->GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(this->GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std:: string& name, const glm::mat4& mat)
{
    glUniformMatrix4fv(this->GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (this->m_UniformLocationCache.find(name) != this->m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(this->m_RendererID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    this->m_UniformLocationCache[name] = location;
    return location;
}