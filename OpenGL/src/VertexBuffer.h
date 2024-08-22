#pragma once


class VertexBuffer
{
private:
	unsigned int m_RendererID; //id of the buffer.
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};