#include "zpch.hpp"
#include "Shader.hpp"

#include "ZEngine/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace ZEngine {
	
	ZEngine::Ref<ZEngine::Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::None: ZE_CORE_ASSERT(false, "RendererAPI::API::None is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);
		}

		ZE_CORE_ASSERT(false, "Unknown RendererAPI::API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::None: ZE_CORE_ASSERT(false, "RendererAPI::API::None is not currently supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
		}

		ZE_CORE_ASSERT(false, "Unknown RendererAPI::API!");
		return nullptr;
	}

}