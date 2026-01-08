#include <Flux.h>
#include <Flux/Core/Entrypoint.h>

class FluxApp : public Flux::Application
{
public:
	FluxApp(const Flux::ApplicationSpecification& spec)
		: Application(spec) {}
	virtual ~FluxApp() {}
};

Flux::Application* Flux::CreateApplication()
{
	Flux::ApplicationSpecification specification;
	specification.Title = "FLUX APP";
	specification.Window.Width = 1280;
	specification.Window.Height = 720;
	return new FluxApp(specification);
}
