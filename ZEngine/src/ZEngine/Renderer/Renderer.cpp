#include "zpch.hpp"
#include "Renderer.hpp"

#include "ZEngine/Renderer/Camera.hpp"

#include "ZEngine/Renderer/Renderer2D.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp" // TODO: Temporary

namespace ZEngine {

	std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const Camera2D& camera)
	{
		s_SceneData->s_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader> shader, const glm::mat4& transform /*= glm::mat4(1.0f)*/)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->s_ViewProjectionMatrix); // TODO: Do this just one
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}