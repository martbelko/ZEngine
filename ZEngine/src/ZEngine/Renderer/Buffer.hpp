#pragma once

namespace ZEngine {

	enum class ShaderDataType : unsigned char
	{
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Bool,
		Mat2, Mat3, Mat4
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ZEngine::ShaderDataType::Float:  return 1 * sizeof(float); break;
		case ZEngine::ShaderDataType::Float2: return 2 * sizeof(float);	break;
		case ZEngine::ShaderDataType::Float3: return 3 * sizeof(float);	break;
		case ZEngine::ShaderDataType::Float4: return 4 * sizeof(float); break;
		case ZEngine::ShaderDataType::Int:    return 1 * sizeof(int); break;
		case ZEngine::ShaderDataType::Int2:   return 2 * sizeof(int); break;
		case ZEngine::ShaderDataType::Int3:   return 3 * sizeof(int); break;
		case ZEngine::ShaderDataType::Int4:   return 4 * sizeof(int); break;
		case ZEngine::ShaderDataType::Bool:   return 1 * sizeof(bool); break;
		case ZEngine::ShaderDataType::Mat2:   return 2 * 2 * sizeof(float); break;
		case ZEngine::ShaderDataType::Mat3:   return 3 * 3 * sizeof(float); break;
		case ZEngine::ShaderDataType::Mat4:   return 4 * 4 * sizeof(float); break;
		}

		ZE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		unsigned int Size;
		unsigned int Offset;
		bool Normalized;

		unsigned int GetComponentCount() const;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) { }
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride();
	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, unsigned int size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;

		static Ref<IndexBuffer> Create(unsigned int* vertices, unsigned int count);
	};

}
