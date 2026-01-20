#pragma once

#include "Flux/Core.h"
#include "Flux/Core/Timestep.h"

#include <entt.hpp>

namespace Flux {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(Timestep ts);

		Entity CreateEntity(const std::string& tag = "Unknown");

	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}
