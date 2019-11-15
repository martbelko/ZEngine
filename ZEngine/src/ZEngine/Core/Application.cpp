#include "zpch.hpp"
#include "Application.hpp"

#include "Platform/Windows/WindowsWindow.hpp"
#include "Platform/Windows/WindowsInput.hpp"
#include "ZEngine/Events/KeyEvent.hpp"
#include "ZEngine/Events/MouseEvent.hpp"

#include "ZEngine/Core/KeyCodes.hpp"
#include "ZEngine/Core/MouseButtonCodes.hpp"

#include "ZEngine/Renderer/Renderer.hpp"

#include <GLFW/glfw3.h>

namespace ZEngine {

	Application* Application::s_pInstance = nullptr;

	Application::Application()
	{
		ZE_CORE_ASSERT(!s_pInstance, "Application already exists!");
		s_pInstance = this;

		Log::Init();

		m_pWindow = std::unique_ptr<Window>(Window::Create(1280, 720, "ZEngine"));
		m_pWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_pWindow->SetVSync(false);

		Renderer::Init();

		m_pImGuiLayer = new ImGuiLayer();
		PushOverlay(m_pImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_bRunning)
		{
			float time = glfwGetTime(); // TODO: Move this to platform, this is GLFW tied!!!
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
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
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

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

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.getNewWidth() == 0 || e.getNewHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(e.getNewWidth(), e.getNewHeight());

		return false;
	}

}
