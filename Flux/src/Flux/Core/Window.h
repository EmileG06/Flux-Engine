#pragma once

#include "Flux/Core.h"
#include "Flux/Events/Event.h"

#include <iostream>
#include <string>
#include <functional>

namespace Flux {

	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width, Height;

		WindowSpecification(const std::string& title = "", uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnEvent(Event& event) = 0;
		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool vsync) = 0;

		virtual void* GetNativeWindow() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static Scope<Window> Create(const WindowSpecification& spec = WindowSpecification());
	};

}
