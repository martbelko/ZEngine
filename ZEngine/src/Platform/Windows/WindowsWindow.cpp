#include "zpch.hpp"
#include "WindowsWindow.hpp"

#include "ZEngine/Events/ApplicationEvent.hpp"
#include "ZEngine/Events/KeyEvent.hpp"
#include "ZEngine/Events/MouseEvent.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"

namespace ZEngine {

	WindowsWindow::WindowsWindow(unsigned int width, unsigned int height, const std::string& title)
	{
		m_WindowData.m_uiWidth = width;
		m_WindowData.m_uiHeight = height;
		m_WindowData.m_strTitle = title;

		int success = glfwInit();
		ZE_CORE_ASSERT(success, "Failed to initialize GLFW!");

		ZE_TRACE("Creating window %, %", width, height);

		m_pNativeWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		m_pContext = new OpenGLContext(m_pNativeWindow);

		glfwSetWindowUserPointer(m_pNativeWindow, &m_WindowData);

		glfwSetWindowSizeCallback(m_pNativeWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				
				WindowResizeEvent e(windowData->m_uiWidth, windowData->m_uiHeight, width, height);

				windowData->m_uiWidth = width;
				windowData->m_uiHeight = height;

				windowData->m_Callback(e);
			});

		glfwSetWindowCloseCallback(m_pNativeWindow, [](GLFWwindow* window)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				WindowCloseEvent e;
				data->m_Callback(e);
			});

		glfwSetKeyCallback(m_pNativeWindow, [](GLFWwindow* winow, int key, int scancode, int action, int mods)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(winow));

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent e(key, 0);
						data->m_Callback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent e(key);
						data->m_Callback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent e(key, 1);
						data->m_Callback(e);
						break;
					}
				}
			});

		glfwSetCharCallback(m_pNativeWindow, [](GLFWwindow* winow, unsigned int codepoint)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(winow));

				KeyTypedEvent e(codepoint);
				data->m_Callback(e);
			});

		glfwSetMouseButtonCallback(m_pNativeWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent e(button);
						data->m_Callback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent e(button);
						data->m_Callback(e);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_pNativeWindow, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseScrolledEvent e(xoffset, yoffset);
				data->m_Callback(e);
			});

		glfwSetCursorPosCallback(m_pNativeWindow, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseMovedEvent e(static_cast<float>(xpos), static_cast<float>(ypos));
				data->m_Callback(e);
			});
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_pNativeWindow);
		glfwTerminate();
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		m_pContext->swapBuffers();
	}

	void WindowsWindow::setEventCallback(const EventCallbackFn& callback)
	{
		m_WindowData.m_Callback = callback;
	}

	unsigned int WindowsWindow::getWidth() const
	{
		return m_WindowData.m_uiWidth;
	}

	unsigned int WindowsWindow::getHeight() const
	{
		return m_WindowData.m_uiHeight;
	}

	void* WindowsWindow::getNativeWindow() const
	{
		return m_pNativeWindow;
	}

	bool WindowsWindow::isVSync() const
	{
		return m_WindowData.m_bVSync;
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_WindowData.m_bVSync = enabled;
	}

	Window* Window::create(unsigned int width, unsigned height, const std::string& title)
	{
		return new WindowsWindow(width, height, title);
	}

}