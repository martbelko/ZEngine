#pragma once

#include "ZEngine/Renderer/RenderCommand.hpp"
#include "ZEngine/Renderer/Shader.hpp"
#include "ZEngine/Renderer/Camera.hpp"

#include <memory>

#include <glm/glm.hpp>

namespace ZEngine {

	class Renderer
	{
	public:
		static void Init();

		static void OnWindowResize(unsigned int width, unsigned int height);

		static void BeginScene(const Camera2D& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader> shader, const glm::mat4& transform = glm::mat4(1.0f));

		static inline RendererAPI::API GetRendererAPI() { return RenderCommand::GetRendererAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 s_ViewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> s_SceneData;
	};

}