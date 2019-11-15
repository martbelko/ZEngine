#pragma once

#include <string>
#include <memory>

#include <glm/glm.hpp>

namespace ZEngine {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& vector) = 0;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
	public:
		static Ref<Shader> Create(const std::string& path);
		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}
