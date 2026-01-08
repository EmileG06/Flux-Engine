#include "FXPch.h"
#include "Texture.h"

#include "Flux/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Flux {

	Ref<Texture2D> Texture2D::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FX_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(filePath);
		}

		FX_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

}
