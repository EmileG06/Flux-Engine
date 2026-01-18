#pragma once

#include "Flux/Core.h"
#include "Flux/Renderer/RendererAPI.h"

namespace Flux {

	enum class RendererType
	{
		None = 0,
		Renderer2D,
		Renderer3D
	};

	class Renderer
	{
	public:
		static void Init(RendererType type);
		static void Shutdown();

		static void OnWindowResized(uint32_t width, uint32_t height);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}
