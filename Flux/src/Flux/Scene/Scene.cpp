#include "FXPch.h"
#include "Scene.h"

#include "Flux/Scene/Entity.h"
#include "Flux/Scene/Components.h"

namespace Flux {

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::OnUpdate(Timestep ts)
	{

	}

	Entity Scene::CreateEntity(const std::string& tag)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(tag);
		entity.AddComponent<TransformComponent>(glm::mat4(1.0f));
		return entity;
	}

}
