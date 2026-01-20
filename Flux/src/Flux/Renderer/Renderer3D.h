#pragma once

#include "Flux/Core.h"
#include "Flux/Renderer/PerspectiveCamera.h"
#include "Flux/Renderer/Mesh.h"

namespace Flux {

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const glm::mat4& viewProjection);
		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();

		static void DrawCube(const glm::mat4& transform, const glm::vec4& color);

		static void DrawMesh(const Mesh& mesh, const glm::mat4& transform, const glm::vec4& color);
	};

}
