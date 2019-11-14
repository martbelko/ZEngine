#include "zpch.hpp"
#include "OpenGLTexture.hpp"

#include <glad/glad.h>

#include <SOIL2/SOIL2.h>

namespace ZEngine {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, nChannels;

		unsigned char* pixels = SOIL_load_image(path.c_str(), &width, &height, &nChannels, 4);
		ZE_CORE_ASSERT(pixels, "Failed to load 2D Texture");
		m_Width = width;
		m_Height = height;
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);

		// TODO: Expose this parameters
		//glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		SOIL_free_image_data(pixels);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	unsigned int OpenGLTexture2D::GetWidth() const
	{
		return m_Width;
	}

	unsigned int OpenGLTexture2D::GetHeight() const
	{
		return m_Height;
	}

	void OpenGLTexture2D::Bind(unsigned int textureUnit /*= 0*/) const
	{
		glBindTextureUnit(textureUnit, m_RendererID);
	}

}