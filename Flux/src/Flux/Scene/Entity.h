#pragma once

#include "Flux/Core.h"
#include "Flux/Scene/Scene.h"

#include <entt.hpp>

namespace Flux {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity entityID, Scene* scene);
		~Entity();

		template <typename T>
		bool HasComponent()
		{
			FX_CORE_ASSERT(m_Scene, "Entity doesn't have a valid scene!");
			return m_Scene->m_Registry.any_of<T>(m_EntityID);
		}

		template <typename T, typename... A>
		T& AddComponent(A&&... args)
		{
			FX_CORE_ASSERT(m_Scene, "Entity doesn't have a valid scene!");
			FX_CORE_ASSERT(!HasComponent<T>(), "Entity already has specified component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<A>(args)...);
		}

		template <typename T>
		T& GetComponent()
		{
			FX_CORE_ASSERT(m_Scene, "Entity doesn't have a valid scene!");
			FX_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have specified component!");
			return m_Scene->m_Registry.get<T>(m_EntityID);
		}

		template <typename T>
		void RemoveComponent()
		{
			FX_CORE_ASSERT(m_Scene, "Entity doesn't have a valid scene!");
			FX_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have specified component!");
			m_Scene->m_Registry.remove<T>(m_EntityID);
		}

		operator bool() const { return m_EntityID != entt::null; }

	private:
		entt::entity m_EntityID = entt::null;
		Scene* m_Scene = nullptr;
	};

}
