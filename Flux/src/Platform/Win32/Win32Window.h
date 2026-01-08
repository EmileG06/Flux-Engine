#pragma once

#include "Flux/Core.h"
#include "Flux/Core/Window.h"
#include "Flux/Renderer/RendererContext.h"

#include <GLFW/glfw3.h>

namespace Flux {

	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowSpecification& spec = WindowSpecification());
		virtual ~Win32Window();

		virtual void OnEvent(Event& e) override;
		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override { return m_Data.Width; }
		virtual uint32_t GetHeight() const override { return m_Data.Height; }

		virtual bool IsVSync() const { return m_Data.VSync; }
		virtual void SetVSync(bool vsync) override;

		virtual void* GetNativeWindow() override { return (void*)m_Handle; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

	private:
		void Init(const WindowSpecification& spec = WindowSpecification());
		void Shutdown();

	private:
		GLFWwindow* m_Handle;
		Ref<RendererContext> m_Context;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
