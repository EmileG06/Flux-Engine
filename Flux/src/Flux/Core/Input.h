#pragma once

#include <iostream>
#include <glm/glm.hpp>

namespace Flux {

	class Input
	{
	public:
		static bool IsKeyPressed(int32_t keycode);

		static bool IsMousePressed(int32_t button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
