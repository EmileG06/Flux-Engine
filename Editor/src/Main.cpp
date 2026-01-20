#include <Flux.h>
#include <Flux/Core/Entrypoint.h>

#include "Editor/EditorLayer.h"

class FluxEditor : public Flux::Application
{
public:
	FluxEditor(const Flux::ApplicationSpecification& spec)
		: Application(spec)
	{
		PushLayer<Flux::EditorLayer>();
	}
};

Flux::Application* Flux::CreateApplication()
{
	Flux::ApplicationSpecification specification;
	specification.Title = "Flux Editor";
	specification.Window.Width = 1920;
	specification.Window.Height = 1080;
	specification.Renderer = RendererType::Renderer3D;
	return new FluxEditor(specification);
}
