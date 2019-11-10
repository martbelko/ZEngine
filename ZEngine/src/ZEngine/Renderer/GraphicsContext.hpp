#pragma once

struct GLFWwindow;

namespace ZEngine {

	class GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual void swapBuffers() = 0;
	};

}
