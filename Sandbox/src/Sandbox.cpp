#include "ZEngine.hpp"

class ExampleLayer : public ZEngine::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer") { }
};

class Sandbox : public ZEngine::Application
{
public:
	Sandbox()
	{
		ZEngine::Application::Get().PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox() override
	{

	}
};

ZEngine::Application* CreateApplication()
{
	return new Sandbox();
}
