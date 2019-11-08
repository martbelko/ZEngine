#include "zpch.hpp"
#include "Application.hpp"

namespace ZEngine {

	Application* Application::s_pInstance = nullptr;

	Application::Application()
	{
		ZE_CORE_ASSERT(!s_pInstance, "Application already exists!");
		s_pInstance = this;

		ZEngine::Log::Init();
	}

	void Application::run()
	{
		std::cout << "Hello\n";
		system("pause");
	}

}