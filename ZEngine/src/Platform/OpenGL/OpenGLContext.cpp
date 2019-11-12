#include "zpch.hpp"
#include "OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ZEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_hWindowHandle(window)
	{
		ZE_CORE_ASSERT(window, "Window handle is null");
		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ZE_CORE_ASSERT(status, "Glad failed to initialize!");

		ZE_CORE_INFO("OpenGL Info:");
		ZE_CORE_INFO("	Renderer: %", glGetString(GL_RENDERER));
		ZE_CORE_INFO("	Vendor: %", glGetString(GL_VENDOR));
		ZE_CORE_INFO("	Version: %", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_hWindowHandle);
	}

}