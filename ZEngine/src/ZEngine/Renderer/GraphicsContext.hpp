#pragma once

struct GLFWwindow;

namespace ZEngine {

	class GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual void SwapBuffers() = 0;
	};

}
