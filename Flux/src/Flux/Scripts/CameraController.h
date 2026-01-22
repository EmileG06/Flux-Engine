#pragma once

#include <Flux/Core.h>
#include <Flux/Core/Input.h>
#include <Flux/Scene/Components.h>
#include <Flux/Scene/ScriptableEntity.h>

namespace Flux {

	class CameraController : public ScriptableEntity
	{
	protected:
		void OnCreate() override
		{
		}

		void OnDestroy() override
		{
		}

		void OnUpdate(Timestep ts) override
		{
			auto& transform = GetComponent<TransformComponent>();
			auto& camera = GetComponent<CameraComponent>();
			float movementOffset = m_CameraSpeed * ts.GetSeconds();

			if (Input::IsKeyPressed(FX_KEY_D))
				transform.Translation -= camera.ViewRight * movementOffset;
			else if (Input::IsKeyPressed(FX_KEY_A))
				transform.Translation += camera.ViewRight * movementOffset;

			if (Input::IsKeyPressed(FX_KEY_W))
				transform.Translation += camera.ViewForward * movementOffset;
			else if (Input::IsKeyPressed(FX_KEY_S))
				transform.Translation -= camera.ViewForward * movementOffset;

			if (Input::IsKeyPressed(FX_KEY_SPACE))
				transform.Translation += camera.ViewUp * movementOffset;
			else if (Input::IsKeyPressed(FX_KEY_Q))
				transform.Translation -= camera.ViewUp * movementOffset;

			camera.Update(transform.Translation);
		}

	private:
		float m_CameraSpeed = 2.5f;
	};

}
