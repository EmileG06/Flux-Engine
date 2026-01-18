#pragma once

#include "Flux/Core.h"
#include "Flux/Renderer/PerspectiveCamera.h"

namespace Flux {

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();

		static void DrawCube(const glm::mat4& transform, const glm::vec4& color);
	};

}
