#pragma once

#include <ZEngine.hpp>

class Sandbox2D : public ZEngine::Layer
{
public:
	Sandbox2D()
		: Layer("ExampleLayer") { }

	virtual void OnAttach() override;

	virtual void OnUpdate(const ZEngine::Timestep& ts) override;

	virtual void OnEvent(ZEngine::Event& event) override;

	bool OnMousePressed(ZEngine::MouseButtonPressedEvent& e);
private:
	ZEngine::Ref<ZEngine::VertexArray> m_SquareVA;
	ZEngine::Ref<ZEngine::Shader> m_Shader;
	std::unique_ptr<ZEngine::Camera2DController> m_CameraController = std::make_unique<ZEngine::Camera2DController>(1280.0f / 720.0f, true);
};
