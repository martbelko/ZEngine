#pragma once

#include "ZEngine/Renderer/GraphicsContext.hpp"

namespace ZEngine {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_hWindowHandle;
	};

}
