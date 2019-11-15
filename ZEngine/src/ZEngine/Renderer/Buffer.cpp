#include "zpch.hpp"
#include "Buffer.hpp"

#include "Renderer.hpp"

#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace ZEngine {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetRendererAPI())
		{
			// TODO: Implement RendererAPI::None
			case RendererAPI::API::None: ZE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		ZE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetRendererAPI())
		{
			// TODO: Implement RendererAPI::None
			case RendererAPI::API::None: ZE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		ZE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		unsigned int offset = 0;
		m_Stride = 0;
		for (BufferElement& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	unsigned int BufferElement::GetComponentCount() const
	{
		switch (Type)
		{
		case ZEngine::ShaderDataType::Float:  return 1; break;
		case ZEngine::ShaderDataType::Float2: return 2; break;
		case ZEngine::ShaderDataType::Float3: return 3; break;
		case ZEngine::ShaderDataType::Float4: return 4; break;
		case ZEngine::ShaderDataType::Int:    return 1; break;
		case ZEngine::ShaderDataType::Int2:   return 2; break;
		case ZEngine::ShaderDataType::Int3:   return 3; break;
		case ZEngine::ShaderDataType::Int4:   return 4; break;
		case ZEngine::ShaderDataType::Bool:   return 1; break;
		case ZEngine::ShaderDataType::Mat2:   return 2 * 2; break;
		case ZEngine::ShaderDataType::Mat3:   return 3 * 3; break;
		case ZEngine::ShaderDataType::Mat4:   return 4 * 4; break;
		}

		ZE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

}