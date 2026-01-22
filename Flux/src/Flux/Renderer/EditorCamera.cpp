#include "FXPch.h"
#include "EditorCamera.h"

#include "Flux/Core/Input.h"
#include "Flux/Core/KeyCodes.h"

namespace Flux {

	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fov),
		m_AspectRatio(aspectRatio),
		m_NearClip(nearClip),
		m_FarClip(farClip),
		Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
	{
		UpdateView();
	}

	void EditorCamera::OnEvent(Event& event)
	{
	}

	void EditorCamera::OnUpdate(Timestep ts)
	{
		const float movementOffset = 2.5f * ts.GetSeconds();

		if (Input::IsKeyPressed(FX_KEY_D))
			m_Position -= m_ViewRight * movementOffset;
		else if (Input::IsKeyPressed(FX_KEY_A))
			m_Position += m_ViewRight * movementOffset;

		if (Input::IsKeyPressed(FX_KEY_W))
			m_Position += m_ViewForward * movementOffset;
		else if (Input::IsKeyPressed(FX_KEY_S))
			m_Position -= m_ViewForward * movementOffset;

		if (Input::IsKeyPressed(FX_KEY_SPACE))
			m_Position += m_ViewUp * movementOffset;
		else if (Input::IsKeyPressed(FX_KEY_Q))
			m_Position -= m_ViewUp * movementOffset;

		UpdateView();
	}

	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
		UpdateView();
	}

	void EditorCamera::UpdateView()
	{
		glm::vec3 forward;
		forward.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		forward.y = glm::sin(glm::radians(m_Pitch));
		forward.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		m_ViewForward = glm::normalize(forward);

		glm::vec3 worldUp = { 0.0f, 1.0f, 0.0f };
		m_ViewRight = glm::normalize(glm::cross(worldUp, m_ViewForward));
		m_ViewUp = glm::normalize(glm::cross(m_ViewForward, m_ViewRight));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_ViewForward, m_ViewUp);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
