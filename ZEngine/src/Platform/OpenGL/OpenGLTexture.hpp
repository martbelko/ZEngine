#pragma once

#include "ZEngine/Renderer/Texture.hpp"

namespace ZEngine {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(unsigned int width, unsigned int height);
		virtual ~OpenGLTexture2D() override;

		virtual void SetData(const void* data, unsigned int size) override;

		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;

		virtual void Bind(unsigned int textureUnit = 0) const override;
	private:
		unsigned int m_RendererID;
		unsigned int m_Width, m_Height;
		std::string m_Path;
	};

}
