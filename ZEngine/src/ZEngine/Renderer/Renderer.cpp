#include "zpch.hpp"
#include "Renderer.hpp"

#include "ZEngine/Renderer/Camera.hpp"

namespace ZEngine {

	std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::BeginScene(const Camera2D& camera)
	{
		s_SceneData->s_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader> shader)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->s_ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}