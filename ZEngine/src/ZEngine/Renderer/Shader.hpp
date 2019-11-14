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
	public:
		static Ref<Shader> Create(const std::string& path);
		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
	};

}
