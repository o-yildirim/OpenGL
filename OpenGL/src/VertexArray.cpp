#include "Renderer.h"
#include "VertexArray.h"


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
	vb.Bind();
    //glVertexAttribPointer parameters below. This should be called after the buffer is bound. vertexAttribPointer basically defines the layout of our buffer.
    //1) Index: Index of the attribute. Position might be on the first index, color is on second, normals are on third etc.
    //2) Size: How many components the selected attribute has. We say 2 because we selected positions (x,y).
    //3) Type: We provide GL_FLOAT
    //4) normalzed: Floats are already normalized, we don't care but if we were working on colors (0,256) 
    //   we might want OpenGL to do it for us or we can do it manually.
    //5) Stride: Amount of bytes between each vertex.
    //6) Pointer: 0 is the position, 12 bytes further we have reached the beginning of the texture coordinates, 8 bytes into that 
    // we get to the vertex normal etc. So for vertex normal, pointer value is 20 to reach the beginning. You can use OFFSET_OF macro etc for that
    // instead of calculating by hand.
    //If we had a struct that contains pos, normals etc. we would say sizeof(<that_struct>) instead of 2 * sizeof(float).
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for(int i = 0; i< elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i); //Here, 0 is the index of the selected attribute which is position.
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void*) offset);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
    
}