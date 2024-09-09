#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    glGenBuffers(1, &m_RendererID); //Init buffer and store the id of it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererID); //Select the buffer you want to use data in. (Draw with buffer with id 5 for instance). It is a basic array.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer()
    :m_Count(0)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    glGenBuffers(1, &m_RendererID); //Init buffer and store the id of it.
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::AddData(const unsigned int* data, unsigned int count)
{
    this->m_Count = count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererID); //Select the buffer you want to use data in. (Draw with buffer with id 5 for instance). It is a basic array.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}