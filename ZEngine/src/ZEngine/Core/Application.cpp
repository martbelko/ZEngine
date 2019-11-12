#include "zpch.hpp"
#include "Application.hpp"

#include "Platform/Windows/WindowsWindow.hpp"
#include "Platform/Windows/WindowsInput.hpp"
#include "ZEngine/Events/KeyEvent.hpp"
#include "ZEngine/Events/MouseEvent.hpp"

#include "ZEngine/Core/KeyCodes.hpp"
#include "ZEngine/Core/MouseButtonCodes.hpp"

#include "ZEngine/Renderer/Renderer.hpp"

namespace ZEngine {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_pInstance = nullptr;

	Application::Application()
	{
		ZE_CORE_ASSERT(!s_pInstance, "Application already exists!");
		s_pInstance = this;

		Log::Init();
		m_pWindow = std::unique_ptr<Window>(Window::Create());
		m_pWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_pImGuiLayer = new ImGuiLayer();
		PushOverlay(m_pImGuiLayer);

		m_VertexArray = VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = {
			0, 1, 2,
		};
		
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
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

		m_Shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);

		std::string squareVertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;

			out vec4 v_Color;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
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

		m_SquareShader = std::make_shared<Shader>(squareVertexSrc, squareFragmentSrc);

		float squareVertices[] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});

		m_SquareVA = VertexArray::Create();
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[] = {
			0, 1, 2,
			1, 3, 2
		};

		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));

		m_SquareVA->SetIndexBuffer(squareIB);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_bRunning)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_SquareShader->Bind();
			Renderer::Submit(m_SquareVA);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_pImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_pImGuiLayer->End();

			m_pWindow->OnUpdate();

			Sleep(10);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto layer = Application::Get().m_LayerStack.end(); layer != Application::Get().m_LayerStack.begin(); )
		{
			(*--layer)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		Application::Get().m_bRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		return false;
	}

}
