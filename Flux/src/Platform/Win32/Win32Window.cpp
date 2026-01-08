#include "FXPch.h"
#include "Win32Window.h"

#include "Flux/Events/WindowEvents.h"
#include "Flux/Events/KeyEvents.h"
#include "Flux/Events/MouseEvents.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Flux {

	static bool s_GLFWInitialized = false;

	Scope<Window> Window::Create(const WindowSpecification& spec)
	{
		return CreateScope<Win32Window>(spec);
	}

	Win32Window::Win32Window(const WindowSpecification& spec)
	{
		Init(spec);
	}

	Win32Window::~Win32Window()
	{
		Shutdown();
	}

	void Win32Window::OnEvent(Event& e)
	{
		if (m_Data.EventCallback)
			m_Data.EventCallback(e);
	}

	void Win32Window::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void Win32Window::SetVSync(bool vsync)
	{
		if (vsync) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.VSync = vsync;
	}

	void Win32Window::Init(const WindowSpecification& spec)
	{
		m_Data.Title = spec.Title;
		m_Data.Width = spec.Width;
		m_Data.Height = spec.Height;

		FX_CORE_INFO("Creating window {0} ({1}, {2})",
			spec.Title, spec.Width, spec.Height);

		if (!s_GLFWInitialized)
		{
			int32_t success = glfwInit();
			FX_CORE_ASSERT(success, "Failed to initialize glfw!");

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			s_GLFWInitialized = true;
		}

		m_Handle = glfwCreateWindow(spec.Width, spec.Height,
			spec.Title.c_str(), nullptr, nullptr);

		FX_CORE_ASSERT(m_Handle, "Window creation failed!");

		m_Context = Ref<OpenGLContext>(new OpenGLContext(m_Handle));
		m_Context->Init();

		glfwSetWindowUserPointer(m_Handle, this);
		SetVSync(true);

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* handle)
			{
				Win32Window& window = *((Win32Window*)glfwGetWindowUserPointer(handle));

				WindowClosedEvent event;
				window.OnEvent(event);
			});

		glfwSetFramebufferSizeCallback(m_Handle, [](GLFWwindow* handle, int32_t width, int32_t height)
			{
				Win32Window& window = *((Win32Window*)glfwGetWindowUserPointer(handle));

				window.m_Data.Width = width;
				window.m_Data.Height = height;

				WindowResizedEvent event = WindowResizedEvent(width, height);
				window.OnEvent(event);
			});

		glfwSetKeyCallback(m_Handle, [](GLFWwindow* handle, int32_t key, int32_t scancode, int32_t action, int32_t mods)
			{
				Win32Window& window = *((Win32Window*)glfwGetWindowUserPointer(handle));

				switch (action)
				{
				case GLFW_PRESS:
				case GLFW_REPEAT:
				{
					KeyPressedEvent event = KeyPressedEvent(key, action == GLFW_REPEAT);
					window.OnEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event = KeyReleasedEvent(key);
					window.OnEvent(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* handle, int32_t button, int32_t action, int32_t mods)
			{
				Win32Window& window = *((Win32Window*)glfwGetWindowUserPointer(handle));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event = MouseButtonPressedEvent(button);
					window.OnEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event = MouseButtonReleasedEvent(button);
					window.OnEvent(event);
					break;
				}
				}
			});

		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* handle, double x, double y)
			{
				Win32Window& window = *((Win32Window*)glfwGetWindowUserPointer(handle));

				MouseMovedEvent event = MouseMovedEvent(static_cast<float>(x), static_cast<float>(y));
				window.OnEvent(event);
			});

		glfwSetScrollCallback(m_Handle, [](GLFWwindow* handle, double x, double y)
			{
				Win32Window& window = *((Win32Window*)glfwGetWindowUserPointer(handle));

				MouseScrolledEvent event = MouseScrolledEvent(static_cast<float>(x), static_cast<float>(y));
				window.OnEvent(event);
			});
	}

	void Win32Window::Shutdown()
	{
		glfwDestroyWindow(m_Handle);
	}

}
