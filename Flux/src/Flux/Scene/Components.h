#pragma once

#include "Flux/Core.h"
#include "Flux/Renderer/Mesh.h"
#include "Flux/Assets/AssetManager.h"

#include <glm/glm.hpp>

namespace Flux {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) { }
	};

	struct TransformComponent
	{
		glm::mat4 Transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) { }

		operator glm::mat4&() { return Transform; }
		operator const glm::mat4&() const { return Transform; }
	};

	struct MeshComponent
	{
		MeshHandle Handle;

		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(MeshHandle handle)
			: Handle(handle) { }

		Mesh* GetMesh() const { return AssetManager::GetMesh(Handle); }
	};

}
