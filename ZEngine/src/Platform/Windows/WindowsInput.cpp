#include "zpch.hpp"
#include "WindowsInput.hpp"

#include <GLFW/glfw3.h>

#include "ZEngine/Core/Application.hpp"

namespace ZEngine {

	Input* Input::s_pInstance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePositionImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::make_pair<float, float>(static_cast<float>(xpos), static_cast<float>(ypos));
	}

	float WindowsInput::getMouseXImpl()
	{
		auto[xpos, ypos] = getMousePositionImpl();
		return xpos;
	}

	float WindowsInput::getMouseYImpl()
	{
		auto [xpos, ypos] = getMousePositionImpl();
		return ypos;
	}

}