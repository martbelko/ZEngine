#pragma once

#include "ZEngine/Renderer/RenderCommand.hpp"

namespace ZEngine {

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static inline RendererAPI::API GetRendererAPI() { return RenderCommand::GetRendererAPI(); }
	};

}