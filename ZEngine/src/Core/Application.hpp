#pragma once

#include "Core/Core.hpp"

namespace ZEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void run();
	private:
		static Application* s_pInstance;
	};

	Application* CreateApplication();

}
