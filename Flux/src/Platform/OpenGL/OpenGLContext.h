#pragma once

#include "Flux/Core.h"
#include "Flux/Renderer/RendererContext.h"

#include <GLFW/glfw3.h>

namespace Flux {

	class OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		virtual ~OpenGLContext() = default;

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}
