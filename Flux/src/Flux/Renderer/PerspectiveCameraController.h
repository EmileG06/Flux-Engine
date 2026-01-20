#pragma once

#include "Flux/Core.h"
#include "Flux/Core/Timestep.h"
#include "Flux/Events/MouseEvents.h"
#include "Flux/Renderer/PerspectiveCamera.h"

namespace Flux {

	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float fov, float aspectRatio, float nearPlane, float farPlane);
		~PerspectiveCameraController();

		void OnEvent(Event& event);
		void OnUpdate(Timestep ts);

		void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

		const PerspectiveCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseMoved(MouseMovedEvent& event);

	private:
		PerspectiveCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 3.0f };
		float m_CameraSpeed = 2.5f;

		glm::vec3 m_CameraRotation = { 0.0f, -90.0f, 0.0f };
		float m_MouseSensitivity = 0.1f;
		float m_LastX = 0.0f, m_LastY = 0.0f;
		bool m_FirstMouse = true;
	};

}
