#include "Texture.h"
#include "std_image/stb_image.h"

Texture::Texture(const std::string& path)
{
	this->m_FilePath = path;
	this->m_RendererID = 0;
	this->m_LocalBuffer = nullptr;
	this->m_Width = 0;
	this->m_Height = 0;
	this->m_BPP = 0;

	stbi_set_flip_vertically_on_load(1); //OpenGL expects textures from start to bottom left (bottom left is 0,0 for openGL).
	this->m_LocalBuffer = stbi_load(path.c_str(), &this->m_Width, &this->m_Height, &this->m_BPP, 4); //4 is RGBA.

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	//If you don't define the following 4 parameters, you'll get a black texture.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //i stands for integer.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //I guess MAG filter scales the image.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //S and T are x and y for textures.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Some of the glTexImage2D parameters:
	//Internalformat: how openGL will store the texture data.
	//Format: format of m_LocalBuffer.
	//We define 8 bits for each channel (GL_RGBA8).
	//We do not want border so 0 pixel border.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE,this->m_LocalBuffer);
	this->Unbind();

	if (m_LocalBuffer)
		stbi_image_free(this->m_LocalBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->m_RendererID);
}

void Texture::Bind(unsigned int slot) const //There are 32 texture slots in glew.
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
