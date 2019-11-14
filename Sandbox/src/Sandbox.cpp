#include <ZEngine.hpp>

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
		vertexBuffer.reset(ZEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{ ZEngine::ShaderDataType::Float3, "a_Position" },
			{ ZEngine::ShaderDataType::Float4, "a_Color" }
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = {
			0, 1, 2,
		};

		ZEngine::Ref<ZEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(ZEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = ZEngine::Shader::Create(vertexSrc, fragmentSrc);

		std::string squareVertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string squareFragmentSrc = R"(
			#version 460 core
			
			uniform vec4 u_Color;

			out vec4 o_Color;

			void main()
			{
				o_Color = u_Color;
			}
		)";

		m_SquareShader = ZEngine::Shader::Create(squareVertexSrc, squareFragmentSrc);

		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};

		ZEngine::Ref<ZEngine::VertexBuffer> squareVB;
		squareVB.reset(ZEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

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
		squareIB.reset(ZEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));

		m_SquareVA->SetIndexBuffer(squareIB);

		m_TextureShader = ZEngine::Shader::Create("assets/shaders/Texture.glsl");
		
		m_Camera = std::make_shared<ZEngine::Camera2D>(-1.6f, 1.6f, -0.9f, 0.9f);
		
		m_CameraPosition = m_Camera->GetPosition();
		m_CameraRotation = m_Camera->GetRotation();

		m_Colors = new glm::vec4[20 * 20];

		for (unsigned int i = 0; i < 20 * 20; ++i)
			m_Colors[i] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

		m_Texture = ZEngine::Texture2D::Create("assets/textures/Plants.png");
	}

	virtual void OnUpdate(const ZEngine::Timestep& ts) override
	{
		if (ZEngine::Input::IsKeyPressed(ZE_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed * ts;
			m_Camera->SetPosition(m_CameraPosition);
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed * ts;
			m_Camera->SetPosition(m_CameraPosition);
		}
		if (ZEngine::Input::IsKeyPressed(ZE_KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed * ts;
			m_Camera->SetPosition(m_CameraPosition);
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed * ts;
			m_Camera->SetPosition(m_CameraPosition);
		}

		if (ZEngine::Input::IsKeyPressed(ZE_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
			m_Camera->SetRotation(m_CameraRotation);
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
			m_Camera->SetRotation(m_CameraRotation);
		}

		if (ZEngine::Input::IsKeyPressed(ZE_KEY_J))
		{
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_L))
		{
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		}
		if (ZEngine::Input::IsKeyPressed(ZE_KEY_I))
		{
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_K))
		{
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;
		}

		ZEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ZEngine::RenderCommand::Clear();

		ZEngine::Renderer::BeginScene(*m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_SquareShader->Bind();

		for (unsigned int i = 0; i < 20; ++i)
		{
			for (unsigned int j = 0; j < 20; ++j)
			{
				glm::vec3 pos = glm::vec3(i * (0.1f + 0.01f), -(float)j * (0.1f + 0.01f), 0.0f) + m_SquarePosition;
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				std::dynamic_pointer_cast<ZEngine::OpenGLShader>(m_SquareShader)->UploadUniformFloat4("u_Color", m_Colors[j * 20 + i]);
				ZEngine::Renderer::Submit(m_SquareVA, m_SquareShader, transform);
			}
		}

		m_Texture->Bind();
		std::dynamic_pointer_cast<ZEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
		ZEngine::Renderer::Submit(m_SquareVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//ZEngine::Renderer::Submit(m_VertexArray, m_Shader);

		ZEngine::Renderer::EndScene();
	}

	virtual void OnEvent(ZEngine::Event& event) override
	{
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
	ZEngine::Ref<ZEngine::Shader> m_Shader, m_SquareShader, m_TextureShader;

	ZEngine::Ref<ZEngine::Texture2D> m_Texture;

	ZEngine::Ref<ZEngine::Camera2D> m_Camera;
	
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;

	float m_CameraRotation;
	float m_CameraRotationSpeed = 180.0f;

	float m_SquareMoveSpeed = 2.0f;

	glm::vec3 m_SquarePosition = glm::vec3(0, 0, 0);

	glm::vec4* m_Colors;
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

