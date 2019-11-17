#pragma once

#include <ZEngine.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>
#include <time.h>

class Quad
{
public:
	Quad(const glm::vec2& position_t, const glm::vec2& size_t)
		: position(position_t), size(size_t)
	{
		position.x -= size.x / 2.0f;
		position.y += size.y / 2.0f;
	}

	glm::vec2 GetPositionForDraw() const { return glm::vec2(position.x + size.x / 2.0f, position.y - size.y / 2.0f); }

	glm::vec2 position;
	glm::vec2 size;
};

class Sandbox2D : public ZEngine::Layer
{
public:
	Sandbox2D()
		: Layer("ExampleLayer") { }

	virtual void OnAttach() override;

	virtual void OnUpdate(const ZEngine::Timestep& ts) override;

	virtual void OnEvent(ZEngine::Event& event) override;

	virtual void OnImGuiRender() override;
private:
	void Restart();
private:
	ZEngine::Ref<ZEngine::VertexArray> m_SquareVA;
	ZEngine::Ref<ZEngine::Shader> m_Shader;
	ZEngine::Ref<ZEngine::Texture> m_Texture = ZEngine::Texture2D::Create("assets/textures/Checkerboard.jpg");
	std::unique_ptr<ZEngine::Camera2D> m_Camera = std::make_unique<ZEngine::Camera2D>(-1280.0f / 720.0f, 1280.0f / 720.0f, -1.0f, 1.0f); // TODO: Window size

	Quad m_Player1 = Quad({ -1.2f, 0.0f }, { 0.04f, 0.25f });
	Quad m_Player2 = Quad({ 1.2f, 0.0f }, { 0.04f, 0.25f });
	glm::vec2 m_PlayerSpeed = { 0.8f, 0.8f };

	Quad m_Ball = Quad({ 0.0f, 0.0f }, { 0.02f, 0.02f });
	glm::vec2 m_BallSpeed = { 1.0f, 1.0f };
	glm::vec2 m_BallDirection = glm::normalize(glm::vec2(0.3f, 0.8f));

	bool m_Paused = true;
};
