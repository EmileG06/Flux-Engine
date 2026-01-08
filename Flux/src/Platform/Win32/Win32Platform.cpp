#include "FXPch.h"
#include "Flux/Core/Platform.h"

#include <GLFW/glfw3.h>

namespace Flux {

	float Platform::GetTime()
	{
		return (float)glfwGetTime();
	}

}
