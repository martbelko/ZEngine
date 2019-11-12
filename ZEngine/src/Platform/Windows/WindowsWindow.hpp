#pragma once

#include <GLFW/glfw3.h>

#include "ZEngine/Core/Window.hpp"
#include "ZEngine/Renderer/GraphicsContext.hpp"

namespace ZEngine {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(unsigned int width, unsigned int height, const std::string& title);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual void SetEventCallback(const EventCallbackFn& callback) override;

		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;

		virtual void* GetNativeWindow() const override;

		virtual bool IsVSync() const override;
		virtual void SetVSync(bool enabled) override;
	private:
		GLFWwindow* m_pNativeWindow;
		GraphicsContext* m_pContext;

		struct WindowData
		{
			unsigned int m_uiWidth, m_uiHeight;
			std::string m_strTitle;

			bool m_bVSync = false;

			EventCallbackFn m_Callback;
		};

		WindowData m_WindowData;
	};

}
