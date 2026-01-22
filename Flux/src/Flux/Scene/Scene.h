#pragma once

#include "Flux/Core.h"
#include "Flux/Core/Timestep.h"
#include "Flux/Renderer/PerspectiveCameraController.h"

#include <entt.hpp>

namespace Flux {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnEvent(Event& event);
		void OnUpdate(Timestep ts);

		Entity CreateEntity(const std::string& tag = "Unknown");
		void DestroyEntity(Entity entity);
		
		void OnViewportResized(uint32_t width, uint32_t height);

	private:
		entt::registry m_Registry;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};

}
