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
	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		while (m_bRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

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

			if (Input::isKeyPressed(ZE_KEY_TAB))
			{
				ZE_CORE_TRACE("Key tab pressed...");
			}

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
