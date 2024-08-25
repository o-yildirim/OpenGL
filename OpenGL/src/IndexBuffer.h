#pragma once
class IndexBuffer
{
private:
	unsigned int m_RendererID; //id of the buffer.
	unsigned int m_Count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	void AddData(const unsigned int* data, unsigned int count);

	inline unsigned int GetCount() const { return m_Count; }
};