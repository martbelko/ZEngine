#include "zpch.hpp"
#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace ZEngine {

	Shader::Shader(const std::string& vertexSource, const std::string fragmentSource)
	{
		// Create an empty vertex shader handle
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = (const char*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = static_cast<char*>(alloca(maxLength * sizeof(char)));
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Log infoLog
			ZE_CORE_ERROR("Vertex shader compilation failed!\n\t");
			ZE_CORE_ERROR(infoLog);

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const char*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = static_cast<char*>(alloca(maxLength * sizeof(char)));
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Log infoLog
			ZE_CORE_ERROR("Fragment shader compilation failed!\n\t");
			ZE_CORE_ERROR(infoLog);

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		unsigned int program = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = static_cast<char*>(alloca(maxLength * sizeof(char)));
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Log infoLog
			ZE_CORE_ERROR("Shader linking failed!\n\t");
			ZE_CORE_ERROR(infoLog);

			// In this simple program, we'll just leave
			return;
		}

		m_RendererID = program;

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}