#include <Flux.h>
#include <Flux/Core/Entrypoint.h>

#include "Editor/EditorLayer.h"
#include "Editor/EditorLayer3D.h"

#define USE_RENDERER_3D 1

class FluxEditor : public Flux::Application
{
public:
	FluxEditor(const Flux::ApplicationSpecification& spec)
		: Application(spec)
	{
#ifndef USE_RENDERER_3D
		PushLayer(new Flux::EditorLayer());
#else
		PushLayer(new Flux::EditorLayer3D());
#endif
	}
};

Flux::Application* Flux::CreateApplication()
{
	Flux::ApplicationSpecification specification;
	specification.Title = "Flux Editor";
	specification.Window.Width = 1920;
	specification.Window.Height = 1080;
#ifndef USE_RENDERER_3D
	specification.Renderer = RendererType::Renderer2D;
#else
	specification.Renderer = RendererType::Renderer3D;
#endif
	return new FluxEditor(specification);
}
