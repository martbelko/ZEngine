#include "ZEngine.hpp"

class Sandbox : public ZEngine::Application
{
public:
	Sandbox()
	{

	}

	virtual ~Sandbox() override
	{

	}
};

ZEngine::Application* CreateApplication()
{
	return new Sandbox();
}
