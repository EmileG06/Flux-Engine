#include "FXPch.h"
#include "PerspectiveCameraController.h"

#include "Flux/Core/Input.h"
#include "Flux/Core/KeyCodes.h"
#include "Flux/Core/MouseCodes.h"

namespace Flux {

	PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio, float nearPlane, float farPlane)
		: m_Camera(fov, aspectRatio, nearPlane, farPlane)
	{
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
	}

	PerspectiveCameraController::~PerspectiveCameraController()
	{
	}

	void PerspectiveCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseMovedEvent>(FX_BIND_EVENT_FN(OnMouseMoved));
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		float movementOffset = m_CameraSpeed * ts.GetSeconds();
		if (Input::IsKeyPressed(FX_KEY_D))
			m_CameraPosition -= m_Camera.GetViewRight() * movementOffset;
		else if (Input::IsKeyPressed(FX_KEY_A))
			m_CameraPosition += m_Camera.GetViewRight() * movementOffset;
		if (Input::IsKeyPressed(FX_KEY_W))
			m_CameraPosition += m_Camera.GetViewForward() * movementOffset;
		else if (Input::IsKeyPressed(FX_KEY_S))
			m_CameraPosition -= m_Camera.GetViewForward() * movementOffset;
		if (Input::IsKeyPressed(FX_KEY_SPACE))
			m_CameraPosition += m_Camera.GetViewUp() * movementOffset;
		else if (Input::IsKeyPressed(FX_KEY_Q))
			m_CameraPosition -= m_Camera.GetViewUp() * movementOffset;
		m_Camera.SetPosition(m_CameraPosition);
	}

	void PerspectiveCameraController::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		m_Camera.SetProjection(fov, aspectRatio, nearPlane, farPlane);
	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& event)
	{
		if (m_FirstMouse)
		{
			m_LastX = event.GetX();
			m_LastY = event.GetY();
			m_FirstMouse = false;
		}

		float xOffset = event.GetX() - m_LastX;
		float yOffset = m_LastY - event.GetY();

		m_LastX = event.GetX();
		m_LastY = event.GetY();

		xOffset *= m_MouseSensitivity;
		yOffset *= m_MouseSensitivity;

		if (Input::IsMousePressed(FX_MOUSE_BUTTON_2))
		{
			m_CameraRotation.x += yOffset;
			m_CameraRotation.y += xOffset;

			m_CameraRotation.x = std::clamp(m_CameraRotation.x, -89.0f, 89.0f);

			m_Camera.SetRotation(m_CameraRotation);
		}

		return false;
	}

}
