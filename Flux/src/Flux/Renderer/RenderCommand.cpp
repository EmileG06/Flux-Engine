#include "FXPch.h"
#include "RenderCommand.h"

namespace Flux {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
