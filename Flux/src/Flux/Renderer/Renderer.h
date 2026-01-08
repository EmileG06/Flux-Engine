#pragma once

#include "Flux/Core.h"
#include "Flux/Renderer/RendererAPI.h"

namespace Flux {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResized(uint32_t width, uint32_t height);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}
