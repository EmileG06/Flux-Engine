#pragma once

#include "Flux/Core.h"
#include "Flux/Renderer/Mesh.h"
#include "Flux/Assets/AssetManager.h"
#include "Flux/Scene/ScriptableEntity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
		glm::vec3 Translation = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) { }

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1.0f, 0.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), Rotation.y, { 0.0f, 1.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), Rotation.z, { 0.0f, 0.0f, 1.0f });

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
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

	struct CameraComponent
	{
		bool MainCamera = false;

		glm::mat4 Projection;
		glm::mat4 View;
		glm::mat4 ViewProjection;

		glm::vec3 Position = { 0.0f, 0.0f, 3.0f };
		glm::vec3 Rotation = { 0.0f, -90.0f, 0.0f };

		glm::vec3 ViewForward;
		glm::vec3 ViewRight;
		glm::vec3 ViewUp;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4& projection)
			: Projection(projection) { }

		void Update()
		{
			glm::vec3 forward;
			forward.x = glm::cos(glm::radians(Rotation.y)) * glm::cos(glm::radians(Rotation.x));
			forward.y = glm::sin(glm::radians(Rotation.x));
			forward.z = glm::sin(glm::radians(Rotation.y)) * glm::cos(glm::radians(Rotation.x));
			ViewForward = glm::normalize(forward);

			glm::vec3 worldUp = { 0.0f, 1.0f, 0.0f };
			ViewRight = glm::normalize(glm::cross(worldUp, ViewForward));
			ViewUp = glm::normalize(glm::cross(ViewForward, ViewRight));

			View = glm::lookAt(Position, Position + ViewForward, { 0.0f, 1.0f, 0.0f });
			ViewProjection = Projection * View;
		}

		const glm::mat4& GetViewProjectionMatrix() const { return ViewProjection; }
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity*(*CreateScript)();
		void(*DestroyScript)(NativeScriptComponent*);

		NativeScriptComponent() = default;
		NativeScriptComponent(const NativeScriptComponent&) = default;

		template <typename T>
		void Bind()
		{
			CreateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* scriptComp)
				{ 
					delete scriptComp->Instance;
					scriptComp->Instance = nullptr;
				};
		}
	};

}
