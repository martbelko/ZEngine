#pragma once

#include "ZEngine/Core/Core.hpp"
#include "ZEngine/Core/Window.hpp"
#include "ZEngine/Core/Layer.hpp"
#include "ZEngine/Core/LayerStack.hpp"
#include "ZEngine/ImGui/ImGuiLayer.hpp"

#include "ZEngine/Events/Event.hpp"
#include "ZEngine/Events/ApplicationEvent.hpp"

namespace ZEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		inline static Application& get() { return *s_pInstance; }

		void run();

		void onEvent(Event& event);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		inline Window& getWindow() { return *m_pWindow; }
	private:
		bool onWindowClose(WindowCloseEvent& event);
		bool onWindowResize(WindowResizeEvent& event);
	private:
		std::unique_ptr<Window> m_pWindow;
		bool m_bRunning = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_pImGuiLayer;
	private:
		static Application* s_pInstance;
	};

}
