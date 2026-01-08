#include "FXPch.h"
#include "Shader.h"

#include "Flux/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Flux {

	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FX_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filePath);
		}

		FX_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: FX_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		FX_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

}
