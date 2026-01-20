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
		auto group = m_Registry.group<TransformComponent, MeshComponent>();
		for (auto entity : group)
		{
			auto [transformComp, meshComp] = group.get(entity);

			Mesh* mesh = meshComp.GetMesh();
			if (mesh)
				Renderer3D::DrawMesh(*mesh, transformComp.Transform, { 0.8f, 0.2f, 0.3f, 1.0f });
		}
	}

	Entity Scene::CreateEntity(const std::string& tag)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(tag);
		entity.AddComponent<TransformComponent>(glm::mat4(1.0f));
		return entity;
	}

}
