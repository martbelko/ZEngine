#include "zpch.hpp"
#include "OpenGLShader.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace ZEngine {

	static unsigned int OpenGLShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		ZE_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::string content = ReadFile(path);
		std::unordered_map<unsigned int, std::string> sources = PreProcess(content);
		Compile(sources);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string fragmentSource)
	{
		std::unordered_map<unsigned int, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			unsigned int size = in.tellg();
			in.seekg(0, std::ios::beg);
			result.resize(size);
			in.read(&result[0], size);
		}
		else
		{
			ZE_CORE_ERROR("Could not open file %", path);
		}

		return result;
	}

	std::unordered_map<unsigned int, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		const std::string typeToken = "#type";
		size_t typeTokenPos = source.find(typeToken, 0);
		std::unordered_map<unsigned int, std::string> res;
		while (typeTokenPos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", typeTokenPos);
			ZE_CORE_ASSERT(eol != std::string::npos, "Unexpected end of file");
			unsigned int count = eol - typeTokenPos - 6;
			std::string shaderType = source.substr(typeTokenPos + 6, count);

			typeTokenPos = source.find(typeToken, typeTokenPos + 6);
			res[OpenGLShaderTypeFromString(shaderType)] = source.substr(eol + 1, typeTokenPos - eol - typeToken.size());
		}

		return res;
	}

	void OpenGLShader::Compile(std::unordered_map<unsigned int, std::string> sources)
	{
		unsigned int program = glCreateProgram();
		std::array<unsigned int, 3> shadersID;
		unsigned int index = 0;
		for (const auto& shaderSource : sources)
		{
			unsigned int shader = glCreateShader(shaderSource.first);
			const char* source = shaderSource.second.c_str();
			glShaderSource(shader, 1, &source, 0);
			glCompileShader(shader);

			int isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				int maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				char* infoLog = (char*)(alloca((maxLength) * sizeof(char)));
				glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

				glDeleteShader(shader);

				ZE_CORE_ERROR("Shader compilation failed!\n\t");
				ZE_CORE_ERROR(infoLog);

				return;
			}

			glAttachShader(program, shader);
			shadersID[index++] = shader;
		}

		glLinkProgram(program);

		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			char* infoLog = static_cast<char*>(alloca(maxLength * sizeof(char)));
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

			glDeleteProgram(program);

			for (unsigned int shaderID : shadersID)
				glDeleteShader(shaderID);

			ZE_CORE_ERROR("Shader linking failed!\n\t");
			ZE_CORE_ERROR(infoLog);

			return;
		}
		
		for (unsigned int shaderID : shadersID)
			glDetachShader(program, shaderID);

		m_RendererID = program;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetUniformFloat4(const std::string& uniformName, const glm::vec4& vec)
	{
		UploadUniformFloat4(uniformName, vec);
	}

	void OpenGLShader::SetUniformMat4(const std::string& uniformName, const glm::mat4& mat)
	{
		UploadUniformMat4(uniformName, mat);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vec)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2fv(location, 1, glm::value_ptr(vec));
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vec)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(vec));
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vec)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(vec));
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::vec2& vec)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2iv(location, 1, (int*)(glm::value_ptr(vec)));
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::vec3& vec)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3iv(location, 1, (int*)(glm::value_ptr(vec)));
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::vec4& vec)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4iv(location, 1, (int*)(glm::value_ptr(vec)));
	}

	void OpenGLShader::UploadUniformMat2(const std::string& name, const glm::mat2& mat)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& mat)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& mat)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

}