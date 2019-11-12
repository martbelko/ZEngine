#include "ZEngine.hpp"

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

		std::shared_ptr<ZEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ZEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{ ZEngine::ShaderDataType::Float3, "a_Position" },
			{ ZEngine::ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = {
			0, 1, 2,
		};

		std::shared_ptr<ZEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(ZEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 460 core
			
			in vec4 v_Color;

			out vec4 o_Color;

			void main()
			{
				o_Color = v_Color;
			}
		)";

		m_Shader = std::make_shared<ZEngine::Shader>(vertexSrc, fragmentSrc);

		std::string squareVertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string squareFragmentSrc = R"(
			#version 460 core
			
			out vec4 o_Color;

			void main()
			{
				o_Color = vec4(0.0, 0.0, 1.0, 1.0);
			}
		)";

		m_SquareShader = std::make_shared<ZEngine::Shader>(squareVertexSrc, squareFragmentSrc);

		float squareVertices[] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<ZEngine::VertexBuffer> squareVB;
		squareVB.reset(ZEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ ZEngine::ShaderDataType::Float3, "a_Position" }
			});

		m_SquareVA = ZEngine::VertexArray::Create();
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = {
			0, 1, 2,
			1, 3, 2
		};

		std::shared_ptr<ZEngine::IndexBuffer> squareIB;
		squareIB.reset(ZEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));

		m_SquareVA->SetIndexBuffer(squareIB);

		m_Camera = std::make_shared<ZEngine::Camera2D>(-1.6f, 1.6f, -0.9f, 0.9f);
		
		m_CameraPosition = m_Camera->GetPosition();
		m_CameraRotation = m_Camera->GetRotation();
	}

	virtual void OnUpdate() override
	{
		if (ZEngine::Input::IsKeyPressed(ZE_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed;
			m_Camera->SetPosition(m_CameraPosition);
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed;
			m_Camera->SetPosition(m_CameraPosition);
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed;
			m_Camera->SetPosition(m_CameraPosition);
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed;
			m_Camera->SetPosition(m_CameraPosition);
		}
		if (ZEngine::Input::IsKeyPressed(ZE_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed;
			m_Camera->SetRotation(m_CameraRotation);
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
			m_Camera->SetRotation(m_CameraRotation);
		}

		ZEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ZEngine::RenderCommand::Clear();

		ZEngine::Renderer::BeginScene(*m_Camera);

		ZEngine::Renderer::Submit(m_SquareVA, m_SquareShader);

		ZEngine::Renderer::Submit(m_VertexArray, m_Shader);

		m_VertexArray->Unbind();

		ZEngine::Renderer::EndScene();
	}

	virtual void OnEvent(ZEngine::Event& event) override
	{

	}
private:
	std::shared_ptr<ZEngine::VertexArray> m_VertexArray;
	std::shared_ptr<ZEngine::VertexArray> m_SquareVA;
	std::shared_ptr<ZEngine::Shader> m_Shader;
	std::shared_ptr<ZEngine::Shader> m_SquareShader;

	std::shared_ptr<ZEngine::Camera2D> m_Camera;
	
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;

	float m_CameraRotation;
	float m_CameraRotationSpeed = 1.0f;
};

class Sandbox : public ZEngine::Application
{
public:
	Sandbox()
	{
		ZEngine::Application::Get().PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox() override
	{

	}
};

ZEngine::Application* CreateApplication()
{
	return new Sandbox();
}
