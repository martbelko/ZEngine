#pragma once

#include "ZEngine/Renderer/Camera.hpp"
#include "ZEngine/Renderer/VertexArray.hpp"
#include "ZEngine/Renderer/Shader.hpp"
#include "ZEngine/Renderer/RenderCommand.hpp"

namespace ZEngine {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera2D& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};

}
