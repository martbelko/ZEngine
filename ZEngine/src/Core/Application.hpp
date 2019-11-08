#pragma once

#include "Core/Core.hpp"

namespace ZEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		inline static Application* Get() { return s_pInstance; }

		void run();
	private:
		bool m_bRunning = true;
	private:
		static Application* s_pInstance;
	};

}
