#pragma once

#include <Flux/Core.h>

#include <glm/glm.hpp>

namespace Flux {

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: m_ProjectionMatrix(projection) { }
		virtual ~Camera() = default;

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

	protected:
		glm::mat4 m_ProjectionMatrix;
	};

}
