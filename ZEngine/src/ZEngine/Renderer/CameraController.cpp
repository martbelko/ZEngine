#include "zpch.hpp"
#include "CameraController.hpp"

#include "ZEngine/Core/Input.hpp"
#include "ZEngine/Core/KeyCodes.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ZEngine {

	Camera2DController::Camera2DController(float aspectRatio, bool rotation /*= false*/)
		: m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(std::make_unique<Camera2D>(-aspectRatio * m_ZoomLevel, aspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)), m_CameraPosition(m_Camera->GetPosition())
	{
	}

	void Camera2DController::OnUpdate(const Timestep& ts)
	{
		if (ZEngine::Input::IsKeyPressed(ZE_KEY_A))
		{
			glm::vec4 dir = { -1, 0, 0, 0 };
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0, 0, 1));
			dir = rotationMatrix * dir;
			m_CameraPosition.x += dir.x * m_CameraSpeed * ts;
			m_CameraPosition.y += dir.y * m_CameraSpeed * ts;
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_D))
		{
			glm::vec4 dir = { 1, 0, 0, 0 };
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0, 0, 1));
			dir = rotationMatrix * dir;
			m_CameraPosition.x += dir.x * m_CameraSpeed * ts;
			m_CameraPosition.y += dir.y * m_CameraSpeed * ts;
		}
		if (ZEngine::Input::IsKeyPressed(ZE_KEY_W))
		{
			glm::vec4 dir = { 0, 1, 0, 0 };
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0, 0, 1));
			dir = rotationMatrix * dir;
			m_CameraPosition.x += dir.x * m_CameraSpeed * ts;
			m_CameraPosition.y += dir.y * m_CameraSpeed * ts;
		}
		else if (ZEngine::Input::IsKeyPressed(ZE_KEY_S))
		{
			glm::vec4 dir = { 0, -1, 0, 0 };
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0, 0, 1));
			dir = rotationMatrix * dir;
			m_CameraPosition.x += dir.x * m_CameraSpeed * ts;
			m_CameraPosition.y += dir.y * m_CameraSpeed * ts;
		}

		if (m_Rotation)
		{
			if (ZEngine::Input::IsKeyPressed(ZE_KEY_Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}
			else if (ZEngine::Input::IsKeyPressed(ZE_KEY_E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}

			m_Camera->SetRotation(m_CameraRotation);
		}

		m_Camera->SetPosition(m_CameraPosition);

		m_CameraSpeed = m_ZoomLevel * 1.5f;
	}

	void Camera2DController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(Camera2DController::OnMouseScrolled));
	}

	bool Camera2DController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.getYOffset() * 0.25f;
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.25f, 5.0f);
		m_Camera->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}