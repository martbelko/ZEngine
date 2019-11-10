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
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_hWindowHandle);
	}

}