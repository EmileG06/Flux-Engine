#include "FXPch.h"
#include "Renderer.h"

#include "Flux/Renderer/RenderCommand.h"
#include "Flux/Renderer/Renderer2D.h"
#include "Flux/Renderer/Renderer3D.h"

namespace Flux {

	void Renderer::Init(RendererType type)
	{
		RenderCommand::Init();

		switch (type)
		{
		case RendererType::None:
		{
			FX_CORE_ASSERT(false, "None is not a supported renderer type!");
			break;
		}
		case RendererType::Renderer2D:
		{
			Renderer2D::Init();
			break;
		}
		case RendererType::Renderer3D:
		{
			Renderer3D::Init();
			break;
		}
		default:
		{
			FX_CORE_ASSERT(false, "Invalid renderer type!");
			break;
		}
		}
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
