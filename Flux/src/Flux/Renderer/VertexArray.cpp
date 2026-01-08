#include "FXPch.h"
#include "VertexArray.h"

#include "Flux/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Flux {

	Ref<VertexArray> Flux::VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FX_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		FX_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

}
