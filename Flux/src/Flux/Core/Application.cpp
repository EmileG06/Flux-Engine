#include "FXPch.h"
#include "Application.h"

#include "Flux/Core/Platform.h"

namespace Flux {

	static Application* s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& spec)
		: m_Specification(spec)
	{
		s_Instance = this;

		if (m_Specification.Window.Title.empty())
			m_Specification.Window.Title = spec.Title;

		m_Window = Window::Create(spec.Window);
		m_Window->SetEventCallback(FX_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init(m_Specification.Renderer);

		m_ImGuiLayer = new ImGuiLayer();
		m_ImGuiLayer->BlockEvents(false);
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	Application& Application::Get()
	{
		FX_CORE_ASSERT(s_Instance, "Application instance was nullptr!");
		return *s_Instance;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(FX_BIND_EVENT_FN(Application::OnWindowClosed));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		m_Running = true;

		while (m_Running)
		{
			float time = Platform::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);

				m_ImGuiLayer->Begin();
				{
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::Stop()
	{
		m_Running = false;
	}

	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		m_Running = false;
		return false;
	}

	bool Application::OnWindowResized(WindowResizedEvent& e)
	{
		if (e.GetWidth() == 0 && e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());

		return false;
	}

}
