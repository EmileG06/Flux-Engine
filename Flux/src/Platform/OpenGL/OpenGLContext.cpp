#include "FXPch.h"
#include "OpenGLContext.h"

namespace Flux {

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window)
	{
		FX_CORE_ASSERT(m_WindowHandle, "Invalid window handle passed to OpenGLContext!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FX_CORE_ASSERT(status, "Failed to initialize GLAD!");

		std::string vendor = (char*)glGetString(GL_VENDOR);
		std::string renderer = (char*)glGetString(GL_RENDERER);
		std::string version = (char*)glGetString(GL_VERSION);

		FX_CORE_INFO("OpenGL Info:");
		FX_CORE_INFO("  Vendor:   {0}", vendor);
		FX_CORE_INFO("  Renderer: {0}", renderer);
		FX_CORE_INFO("  Version:  {0}", version);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
