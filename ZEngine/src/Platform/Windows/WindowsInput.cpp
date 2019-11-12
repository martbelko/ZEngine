#include "zpch.hpp"
#include "WindowsInput.hpp"

#include <GLFW/glfw3.h>

#include "ZEngine/Core/Application.hpp"

namespace ZEngine {

	Input* Input::s_pInstance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::make_pair<float, float>(static_cast<float>(xpos), static_cast<float>(ypos));
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[xpos, ypos] = GetMousePositionImpl();
		return xpos;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [xpos, ypos] = GetMousePositionImpl();
		return ypos;
	}

}