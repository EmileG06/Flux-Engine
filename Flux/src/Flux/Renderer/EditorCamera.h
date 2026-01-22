#pragma once

#include <Flux/Core.h>
#include <Flux/Core/Timestep.h>
#include <Flux/Renderer/Camera.h>

namespace Flux {

	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearPlane, float farPlane);
		virtual ~EditorCamera() = default;

		void OnEvent(Event& event);
		void OnUpdate(Timestep ts);

		void SetViewportSize(float width, float height)
		{ 
			m_ViewportWidth = width;
			m_ViewportHeight = height;
			UpdateProjection();
		}

		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void UpdateProjection();
		void UpdateView();

	private:
		float m_FOV;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 3.0f };
		float m_Pitch = 0.0f, m_Yaw = -90.0f;

		glm::vec3 m_ViewForward;
		glm::vec3 m_ViewRight;
		glm::vec3 m_ViewUp;

		float m_ViewportWidth = 1920.0f, m_ViewportHeight = 1080.0f;
	};

}
