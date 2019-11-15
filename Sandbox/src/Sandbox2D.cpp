#include "Sandbox2D.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Platform/OpenGL/OpenGLShader.hpp>

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnUpdate(const ZEngine::Timestep& ts)
{
	m_CameraController->OnUpdate(ts);

	ZEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ZEngine::RenderCommand::Clear();

	ZEngine::Renderer2D::BeginScene(m_CameraController->GetCamera());

	ZEngine::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 5.0f, 5.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });

	ZEngine::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(ZEngine::Event& event)
{
	m_CameraController->OnEvent(event);
}

