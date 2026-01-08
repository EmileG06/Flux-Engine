#include "FXPch.h"
#include "Renderer.h"

#include "Flux/Renderer/RenderCommand.h"
#include "Flux/Renderer/Renderer2D.h"

namespace Flux {

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

}
