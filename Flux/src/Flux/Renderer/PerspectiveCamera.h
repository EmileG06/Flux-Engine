#pragma once

namespace Flux {

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera() = default;
		PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane);

		void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position)
		{
			m_Position = position;
			CalculateViewMatrix();
		}

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec3& rotation)
		{
			m_Rotation = rotation;
			CalculateViewMatrix();
		}

		const glm::vec3& GetViewForward() const { return m_ViewForward; }
		const glm::vec3& GetViewRight() const { return m_ViewRight; }
		const glm::vec3& GetViewUp() const { return m_ViewUp; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void CalculateViewMatrix();

	private:
		float m_FOV = glm::radians(45.0f);
		float m_AspectRatio = 1.778f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;

		glm::vec3 m_Position = { 0.0f, 0.0f, 3.0f };
		glm::vec3 m_Rotation = { 0.0f, -90.0f, 0.0f };

		glm::vec3 m_ViewForward = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_ViewRight = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_ViewUp = { 0.0f, 0.0f, 0.0f };

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};

}
