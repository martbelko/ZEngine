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

	void ShaderLibrary::Add(const std::string& name, Ref<Shader>& shader)
	{
		ZE_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader name in shader library already exists!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		ZE_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader name in shader library already exists!");
		m_Shaders[name] = Shader::Create(filepath);
		return m_Shaders[name];
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		ZE_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader is not in shader library!");
		return m_Shaders[name];
	}

}