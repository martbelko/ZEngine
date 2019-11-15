#pragma once

#include "ZEngine/Renderer/RendererAPI.hpp"

namespace ZEngine {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

		virtual void SetViewport(int x, int y, unsigned int width, unsigned int height) override;
	};

}
