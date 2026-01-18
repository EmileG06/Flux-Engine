#include "FXPch.h"
#include "PerspectiveCamera.h"

namespace Flux {

	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane)
		: m_FOV(glm::radians(fov)), m_AspectRatio(aspectRatio), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane);
		CalculateViewMatrix();
	}

	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		m_FOV = glm::radians(fov);
		m_AspectRatio = aspectRatio;
		m_NearPlane = nearPlane;
		m_FarPlane = farPlane;
		m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane);
		CalculateViewMatrix();
	}

	void PerspectiveCamera::CalculateViewMatrix()
	{
		glm::vec3 forward;
		forward.x = glm::cos(glm::radians(m_Rotation.y)) * glm::cos(glm::radians(m_Rotation.x));
		forward.y = glm::sin(glm::radians(m_Rotation.x));
		forward.z = glm::sin(glm::radians(m_Rotation.y)) * glm::cos(glm::radians(m_Rotation.x));
		m_ViewForward = glm::normalize(forward);

		glm::vec3 worldUp = { 0.0f, 1.0f, 0.0f };
		m_ViewRight = glm::normalize(glm::cross(worldUp, m_ViewForward));
		m_ViewUp = glm::normalize(glm::cross(m_ViewForward, m_ViewRight));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_ViewForward, m_ViewUp);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
