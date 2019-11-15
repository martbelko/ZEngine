#pragma once

#include "ZEngine/Renderer/Shader.hpp"

namespace ZEngine {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& vertexSource, const std::string fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void SetUniformFloat4(const std::string& name, const glm::vec4& vector) override;

		void SetUniformMat4(const std::string& uniformName, const glm::mat4& matrix) override;

		void UploadUniformFloat(const std::string& uniformName, float value);
		void UploadUniformFloat2(const std::string& uniformName, const glm::vec2& vector);
		void UploadUniformFloat3(const std::string& uniformName, const glm::vec3& vector);
		void UploadUniformFloat4(const std::string& uniformName, const glm::vec4& vector);

		void UploadUniformInt(const std::string& uniformName, int value);
		void UploadUniformInt2(const std::string& uniformName, const glm::vec2& vector);
		void UploadUniformInt3(const std::string& uniformName, const glm::vec3& vector);
		void UploadUniformInt4(const std::string& uniformName, const glm::vec4& vector);

		void UploadUniformMat2(const std::string& uniformName, const glm::mat2& matrix);
		void UploadUniformMat3(const std::string& uniformName, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<unsigned int, std::string> PreProcess(const std::string& source);
		void Compile(std::unordered_map<unsigned int, std::string> sources);
	private:
		unsigned int m_RendererID;
	};

}
