#pragma once

#include "RendererAPI.hpp"

namespace ZEngine {

	class RenderCommand
	{
	public:
		static inline void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		static inline void Clear()
		{
			s_RendererAPI->Clear();
		}

		static inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		static inline RendererAPI::API GetRendererAPI() { return s_RendererAPI->GetRendererAPI(); }
	private:
		static std::unique_ptr<RendererAPI> s_RendererAPI;
	};

}
