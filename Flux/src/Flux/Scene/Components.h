#pragma once

#include "Flux/Core.h"

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

}
