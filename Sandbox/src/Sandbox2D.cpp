#include "Sandbox2D.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>

#include <C:\dev\C++\ZEngine\ZEngine\vendor\ImGui\imgui.h>

static bool IsInCollision(const Quad& q1, const Quad& q2)
{
	bool a = q1.position.x + q1.size.x >= q2.position.x;
	bool b = q1.position.x <= q2.position.x + q2.size.x;
	bool c = q1.position.y - q1.size.y <= q2.position.y;
	bool d = q1.position.y >= q2.position.y - q2.size.y;
	/*if (q1.position.x + q1.size.x >= q2.position.x &&
		q1.position.x <= q2.position.x + q2.size.x &&
		q1.position.y - q1.size.y >= q2.position.y &&
		q1.position.y <= q2.position.y - q2.size.y)
	{
		return true;
	}*/
	return a && b && c && d;
}

static glm::vec2 vecs[] = {
	{ 0.8f, 0.4f },
	{ 0.8f, 0.3f },
	{ 0.8f, 0.2f },
	{ 0.8f, 0.1f },
	{ 0.8f, -0.4f },
	{ 0.8f, -0.3f },
	{ 0.8f, -0.2f },
	{ 0.8f, -0.1f }
};

void Sandbox2D::OnAttach()
{
	srand(time(NULL));
}

void Sandbox2D::OnUpdate(const ZEngine::Timestep& ts)
{
	// UPDATE
	// Player moves
	if (ZEngine::Input::IsKeyPressed(ZE_KEY_W))
	{
		m_Player1.position.y += m_PlayerSpeed.y * ts;
	}
	else if (ZEngine::Input::IsKeyPressed(ZE_KEY_S))
	{
		m_Player1.position.y -= m_PlayerSpeed.y * ts;
	}

	if (ZEngine::Input::IsKeyPressed(ZE_KEY_UP))
	{
		m_Player2.position.y += m_PlayerSpeed.y * ts;
	}
	else if (ZEngine::Input::IsKeyPressed(ZE_KEY_DOWN))
	{
		m_Player2.position.y -= m_PlayerSpeed.y * ts;
	}

	// Border check
	if (m_Ball.position.x + m_Ball.size.x >= 1280.0f / 720.0f) 
	{
		//m_BallDirection = glm::reflect(m_BallDirection, glm::vec2(1.0f, 0.0f));

	}
	else if (m_Ball.position.x <= -1280.0f / 720.0f)
	{
		m_BallDirection = glm::reflect(m_BallDirection, glm::vec2(1.0f, 0.0f));
	}

	if (m_Ball.position.y >= 1.0f)
	{
		m_BallDirection = glm::reflect(m_BallDirection, glm::vec2(0.0f, 1.0f));
	}
	else if (m_Ball.position.y - m_Ball.size.y <= -1.0f)
	{
		m_BallDirection = glm::reflect(m_BallDirection, glm::vec2(0.0f, 1.0f));
	}

	if (IsInCollision(m_Ball, m_Player1))
	{
		m_BallDirection = vecs[rand() % 4];
		m_BallDirection = glm::normalize(m_BallDirection);
		m_BallSpeed *= glm::vec2(1.01f, 1.01f);
	}
	else if (IsInCollision(m_Ball, m_Player2))
	{
		m_BallDirection = -vecs[rand() % 8];
		m_BallDirection = glm::normalize(m_BallDirection);
		m_BallSpeed *= glm::vec2(1.01f, 1.01f);
	}

	m_Ball.position.x += m_BallDirection.x * m_BallSpeed.x * ts;
	m_Ball.position.y += m_BallDirection.y * m_BallSpeed.y * ts;

	// RENDER
	ZEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ZEngine::RenderCommand::Clear();

	ZEngine::Renderer2D::BeginScene(*m_Camera);

	ZEngine::Renderer2D::DrawQuad(m_Player1.GetPositionForDraw(), m_Player1.size, m_Texture, { 0.5f, 0.1f, 0.1f, 1.0f });
	ZEngine::Renderer2D::DrawQuad(m_Player2.GetPositionForDraw(), m_Player2.size, m_Texture, { 0.1f, 0.1f, 0.5f, 1.0f });

	ZEngine::Renderer2D::DrawQuad(m_Ball.GetPositionForDraw(), m_Ball.size, { 1.0f, 1.0f, 1.0f, 1.0f });
}

void Sandbox2D::OnEvent(ZEngine::Event& event)
{
	//m_CameraController->OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
}

void Sandbox2D::Restart()
{
	m_Player1 = Quad({ -1.2f, 0.0f }, { 0.04f, 0.25f });
	m_Player2 = Quad({ 1.2f, 0.0f }, { 0.04f, 0.25f });
	m_PlayerSpeed = { 0.8f, 0.8f };

	m_Ball = Quad({ 0.0f, 0.0f }, { 0.02f, 0.02f });
	m_BallSpeed = { 1.0f, 1.0f };
	m_BallDirection = glm::normalize(glm::vec2(0.3f, 0.8f));
}
