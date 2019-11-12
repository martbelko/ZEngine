#pragma once

#include <string>
#include <glm/glm.hpp>

namespace ZEngine {

	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix);
	private:
		unsigned int m_RendererID;
	};

}
