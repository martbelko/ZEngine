#include "zpch.hpp"
#include "Renderer2D.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace ZEngine {

	struct Renderer2DStorage
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
	};

	static Renderer2DStorage* s_Data = new Renderer2DStorage();

	void Renderer2D::Init()
	{
		s_Data->vertexArray = ZEngine::VertexArray::Create();

		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f
		};

		ZEngine::Ref<ZEngine::VertexBuffer> squareVB;
		squareVB = ZEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ ZEngine::ShaderDataType::Float3, "a_Position" },
			});

		s_Data->vertexArray->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = {
			0, 1, 2,
			1, 3, 2
		};

		ZEngine::Ref<ZEngine::IndexBuffer> squareIB;
		squareIB = ZEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));

		s_Data->vertexArray->SetIndexBuffer(squareIB);

		s_Data->shader = ZEngine::Shader::Create("assets/shaders/Sandbox2D.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const Camera2D& camera)
	{
		s_Data->shader->Bind();
		s_Data->shader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->shader->Bind();
		s_Data->shader->SetUniformFloat4("u_Color", color);
		s_Data->shader->SetUniformMat4("u_Transform", transform);

		s_Data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);
	}

}