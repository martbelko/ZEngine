#pragma once

#include "ZEngine/Renderer/Camera.hpp"

#include "ZEngine/Events/Event.hpp"
#include "ZEngine/Events/MouseEvent.hpp"
#include "ZEngine/Events/KeyEvent.hpp"
#include "ZEngine/Events/ApplicationEvent.hpp"

#include "ZEngine/Core/Timestep.hpp"

#include <memory>

namespace ZEngine {

	class Camera2DController
	{
	public:
		Camera2DController(float aspectRatio, bool rotation = false);

		void OnUpdate(const Timestep& timestep);
		void OnEvent(Event& event);

		inline Camera2D& GetCamera() { return *m_Camera; }
		inline const Camera2D& GetCamera() const { return *m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		float m_ZoomLevel = 1.0f;
		float m_AspectRatio;
		bool m_Rotation;

		std::unique_ptr<Camera2D> m_Camera;

		glm::vec3 m_CameraPosition;
		float m_CameraRotation = 0.0f;

		float m_CameraSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};

}