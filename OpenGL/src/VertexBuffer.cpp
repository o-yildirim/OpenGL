#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID); //Init buffer and store the id of it.
    this->AddData(data, size);
}

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_RendererID);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::AddData(const void* data, unsigned int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererID); //Select the buffer you want to use data in. (Draw with buffer with id 5 for instance). It is a basic array.
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //We binded the buffer one line above. It knows which one to draw from.
}

void VertexBuffer::UpdateData(const void* data, unsigned int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererID); //Select the buffer you want to use data in. (Draw with buffer with id 5 for instance). It is a basic array.
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data); //We binded the buffer one line above. It knows which one to draw from.
}

