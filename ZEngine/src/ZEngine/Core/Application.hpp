#pragma once

#include "ZEngine/Core/Core.hpp"
#include "ZEngine/Core/Window.hpp"
#include "ZEngine/Core/Layer.hpp"
#include "ZEngine/Core/LayerStack.hpp"
#include "ZEngine/ImGui/ImGuiLayer.hpp"

#include "ZEngine/Events/Event.hpp"
#include "ZEngine/Events/ApplicationEvent.hpp"

#include "ZEngine/Renderer/Buffer.hpp"
#include "ZEngine/Renderer/VertexArray.hpp"
#include "ZEngine/Renderer/Shader.hpp"
#include "ZEngine/Renderer/Camera.hpp"

namespace ZEngine {

	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	class Application
	{
	public:
		Application();
		virtual ~Application();

		inline static Application& Get() { return *s_pInstance; }

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_pWindow; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		std::unique_ptr<Window> m_pWindow;
		bool m_bRunning = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_pImGuiLayer;
	private:
		static Application* s_pInstance;
	};

}
