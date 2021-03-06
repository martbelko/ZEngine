#include "zpch.hpp"
#include "OpenGLVertexArray.hpp"

#include <glad/glad.h>

namespace ZEngine {

	static unsigned int shaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ZEngine::ShaderDataType::Float:
		case ZEngine::ShaderDataType::Float2:
		case ZEngine::ShaderDataType::Float3:
		case ZEngine::ShaderDataType::Float4:
		case ZEngine::ShaderDataType::Mat2:
		case ZEngine::ShaderDataType::Mat3:
		case ZEngine::ShaderDataType::Mat4:
			return GL_FLOAT; break;
		case ZEngine::ShaderDataType::Int:
		case ZEngine::ShaderDataType::Int2:
		case ZEngine::ShaderDataType::Int3:
		case ZEngine::ShaderDataType::Int4:
			return GL_INT; break;
		case ZEngine::ShaderDataType::Bool:
			return GL_BOOL; break;
		}

		ZE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);

		unsigned int index = 0;
		const BufferLayout& layout = vertexBuffer->GetLayout();
		for (const BufferElement& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				shaderDataTypeToOpenGLType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			++index;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}


	const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

}
