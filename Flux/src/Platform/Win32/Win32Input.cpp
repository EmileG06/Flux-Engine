#include "FXPch.h"
#include "Flux/Core/Input.h"

#include "Flux/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Flux {

	bool Input::IsKeyPressed(int32_t keycode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
		int32_t state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMousePressed(int32_t button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
		int32_t state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());

		double x = 0.0, y = 0.0;
		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}

	float Input::GetMouseX()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());

		double x = 0.0, y = 0.0;
		glfwGetCursorPos(window, &x, &y);

		return (float)x;
	}

	float Input::GetMouseY()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());

		double x = 0.0, y = 0.0;
		glfwGetCursorPos(window, &x, &y);

		return (float)y;
	}

}
