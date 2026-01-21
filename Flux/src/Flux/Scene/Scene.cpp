#include "FXPch.h"
#include "Scene.h"

#include "Flux/Scene/Entity.h"
#include "Flux/Scene/Components.h"
#include "Flux/Renderer/RenderCommand.h"
#include "Flux/Renderer/Renderer3D.h"

namespace Flux {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::OnEvent(Event& event)
	{
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// -----------------------
		// --- Update ------------
		// -----------------------

		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& scriptComp)
			{
				// TODO: This should happen when you play the scene (OnScenePlay)
				if (!scriptComp.Instance)
				{
					scriptComp.Instance = scriptComp.CreateScript();
					FX_CORE_ASSERT(scriptComp.Instance, "Failed to create ScriptableEntity instance!");

					scriptComp.Instance->m_Entity = { entity, this };
					scriptComp.Instance->OnCreate();
				}

				scriptComp.Instance->OnUpdate(ts);
			});

		// -----------------------
		// --- Render ------------
		// -----------------------

		{
			auto view = m_Registry.view<TransformComponent, MeshComponent>();
			for (auto entity : view)
			{
				auto [transformComp, meshComp] = view.get<TransformComponent, MeshComponent>(entity);

				Mesh* mesh = meshComp.GetMesh();
				if (mesh)
					Renderer3D::DrawMesh(*mesh, transformComp.GetTransform(), {0.8f, 0.2f, 0.3f, 1.0f});
			}
		}
	}

	Entity Scene::CreateEntity(const std::string& tag)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(tag);
		entity.AddComponent<TransformComponent>(glm::vec3(0.0f));
		return entity;
	}

	void Scene::OnViewportResized(uint32_t width, uint32_t height)
	{
		float aspectRatio = (float)width / (float)height;

		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComp = view.get<CameraComponent>(entity);
			cameraComp.Projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 1000.0f);
		}
	}

}
