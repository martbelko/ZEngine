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
		static void BeginScene(const Camera2D& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader> shader);

		static inline RendererAPI::API GetRendererAPI() { return RenderCommand::GetRendererAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 s_ViewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> s_SceneData;
	};

}