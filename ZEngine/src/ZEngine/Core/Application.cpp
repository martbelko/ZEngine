#include "zpch.hpp"
#include "Application.hpp"

#include <glad/glad.h>

#include "Platform/Windows/WindowsWindow.hpp"
#include "Platform/Windows/WindowsInput.hpp"
#include "ZEngine/Events/KeyEvent.hpp"
#include "ZEngine/Events/MouseEvent.hpp"

#include "ZEngine/Core/KeyCodes.hpp"
#include "ZEngine/Core/MouseButtonCodes.hpp"

namespace ZEngine {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_pInstance = nullptr;

	Application::Application()
	{
		ZE_CORE_ASSERT(!s_pInstance, "Application already exists!");
		s_pInstance = this;

		Log::Init();
		m_pWindow = std::unique_ptr<Window>(Window::create());
		m_pWindow->setEventCallback(BIND_EVENT_FN(onEvent));

		m_pImGuiLayer = new ImGuiLayer();
		pushOverlay(m_pImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[] = {
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 460 core
			
			out vec4 o_Color;

			void main()
			{
				o_Color = vec4(1.0, 0.0, 0.0, 1.0);
			}

		)";

		m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		while (m_bRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			m_Shader->bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->onUpdate();
			}

			m_pImGuiLayer->begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->onImGuiRender();
			}
			m_pImGuiLayer->end();

			m_pWindow->onUpdate();

			Sleep(10);
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_LayerStack.pushOverlay(layer);
		layer->onAttach();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		for (auto layer = Application::get().m_LayerStack.end(); layer != Application::get().m_LayerStack.begin(); )
		{
			(*--layer)->onEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		Application::get().m_bRunning = false;
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& event)
	{
		return false;
	}

}
