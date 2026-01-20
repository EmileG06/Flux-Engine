#pragma once

#include "Flux/Core.h"
#include "Flux/Core/Window.h"
#include "Flux/Events/Event.h"
#include "Flux/Events/WindowEvents.h"
#include "Flux/Core/LayerStack.h"
#include "Flux/ImGui/ImGuiLayer.h"
#include "Flux/Renderer/Renderer.h"

namespace Flux {

	struct ApplicationSpecification
	{
		std::string Title = "Flux Application";
		WindowSpecification Window;
		RendererType Renderer;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& spec = ApplicationSpecification());
		virtual ~Application();

		static Application& Get();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		template <typename T>
		requires(std::is_base_of_v<Layer, T>)
		void PushLayer()
		{
			PushLayer(new T());
		}

		template <typename T>
		requires(std::is_base_of_v<Layer, T>)
		void PushOverlay()
		{
			PushOverlay(new T());
		}

		void OnEvent(Event& e);

		void Run();
		void Stop();

		Scope<Window>& GetWindow() { return m_Window; }

	private:
		bool OnWindowClosed(WindowClosedEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);

	private:
		ApplicationSpecification m_Specification;

		Scope<Window> m_Window;
		bool m_Running = false;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer = nullptr;
	};

	Application* CreateApplication();

}
