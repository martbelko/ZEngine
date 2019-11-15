#include <ZEngine.hpp>
#include <ZEngine/Core/EntryPoint.hpp>

#include "Sandbox2D.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <Platform/OpenGL/OpenGLShader.hpp>

class ExampleLayer : public ZEngine::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer") { }

	virtual void OnAttach() override
	{
		m_VertexArray = ZEngine::VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f
		};

		ZEngine::Ref<ZEngine::VertexBuffer> vertexBuffer;
		vertexBuffer = ZEngine::VertexBuffer::Create(vertices, sizeof(vertices));

		vertexBuffer->SetLayout({
			{ ZEngine::ShaderDataType::Float3, "a_Position" },
			{ ZEngine::ShaderDataType::Float4, "a_Color" }
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = {
			0, 1, 2,
		};

		ZEngine::Ref<ZEngine::IndexBuffer> indexBuffer;
		indexBuffer = ZEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_ShaderLibrary.Load("Square", "assets/shaders/Square.glsl");

		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};

		ZEngine::Ref<ZEngine::VertexBuffer> squareVB;
		squareVB = ZEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ ZEngine::ShaderDataType::Float3, "a_Position" },
			{ ZEngine::ShaderDataType::Float2, "a_TexCoords" }
		});

		m_SquareVA = ZEngine::VertexArray::Create();
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = {
			0, 1, 2,
			1, 3, 2
		};

		ZEngine::Ref<ZEngine::IndexBuffer> squareIB;
		squareIB = ZEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));

		m_SquareVA->SetIndexBuffer(squareIB);

		m_ShaderLibrary.Load("Texture", "assets/shaders/Texture.glsl");
		
		//m_CameraController = std::make_unique<ZEngine::Camera2DController>(1280.0f / 720.0f, false);
		
		m_Colors = new glm::vec4[20 * 20];

		for (unsigned int i = 0; i < 20 * 20; ++i)
			m_Colors[i] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

		m_Texture = ZEngine::Texture2D::Create("assets/textures/Plants.png");
	}

	virtual void OnUpdate(const ZEngine::Timestep& ts) override
	{
		m_CameraController->OnUpdate(ts);

		ZEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ZEngine::RenderCommand::Clear();

		ZEngine::Renderer::BeginScene(m_CameraController->GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_ShaderLibrary.Get("Square")->Bind();

		for (unsigned int i = 0; i < 20; ++i)
		{
			for (unsigned int j = 0; j < 20; ++j)
			{
				glm::vec3 pos = glm::vec3(i * (0.1f + 0.01f), -(float)j * (0.1f + 0.01f), 0.0f) + m_SquarePosition;
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				std::dynamic_pointer_cast<ZEngine::OpenGLShader>(m_ShaderLibrary.Get("Square"))->UploadUniformFloat4("u_Color", m_Colors[j * 20 + i]);
				ZEngine::Renderer::Submit(m_SquareVA, m_ShaderLibrary.Get("Square"), transform);
			}
		}

		m_Texture->Bind();
		std::dynamic_pointer_cast<ZEngine::OpenGLShader>(m_ShaderLibrary.Get("Texture"))->UploadUniformInt("u_Texture", 0);
		ZEngine::Renderer::Submit(m_SquareVA, m_ShaderLibrary.Get("Texture"), glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		ZEngine::Renderer::EndScene();
	}

	virtual void OnEvent(ZEngine::Event& event) override
	{
		m_CameraController->OnEvent(event);
		ZEngine::EventDispatcher dispatcher(event);
		dispatcher.dispatch<ZEngine::MouseButtonPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnMousePressed));
	}

	bool OnMousePressed(ZEngine::MouseButtonPressedEvent& e)
	{
		static unsigned int i = 0;
		if (e.getButton() == ZE_MOUSE_BUTTON_1)
		{
			m_Colors[i] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
			++i;
		}

		return false;
	}
private:
	ZEngine::Ref<ZEngine::VertexArray> m_VertexArray;
	ZEngine::Ref<ZEngine::VertexArray> m_SquareVA;
	ZEngine::ShaderLibrary m_ShaderLibrary;

	ZEngine::Ref<ZEngine::Texture2D> m_Texture;

	std::unique_ptr<ZEngine::Camera2DController> m_CameraController = std::make_unique<ZEngine::Camera2DController>(1280.0f / 720.0f, true);

	float m_SquareMoveSpeed = 2.0f;

	glm::vec3 m_SquarePosition = glm::vec3(0, 0, 0);

	glm::vec4* m_Colors;
};


class Sandbox : public ZEngine::Application
{
public:
	Sandbox()
	{
		//ZEngine::Application::Get().PushLayer(new ExampleLayer());
		ZEngine::Application::Get().PushLayer(new Sandbox2D());
	}

	virtual ~Sandbox() override
	{
	}
};

ZEngine::Application* CreateApplication()
{
	return new Sandbox();
}

