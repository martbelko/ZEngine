#pragma once

#include <glm/glm.hpp>

#include "ZEngine/Renderer/VertexArray.hpp"

namespace ZEngine {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL
		};
	public:
		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		virtual void SetViewport(int x, int y, unsigned int width, unsigned int height) = 0;
	public:
		static inline API GetRendererAPI() { return s_API; }
	private:
		static API s_API;
	};

}
