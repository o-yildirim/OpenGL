#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP; // BPP = Bits per Pixel of the actual texture.

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const; //In OpenGl, you bind textures to slots. For ex. windows has 24 texture slots etc. You can ask
											//OpenGL "how many texture slots I have?"
	void Unbind() const;

	inline int GetWidth() const { return this->m_Width; }
	inline int GetHeight() const { return this->m_Height;  }

};
