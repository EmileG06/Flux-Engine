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
		operator uint32_t() const { return (uint32_t)m_EntityID; }
		operator entt::entity() const { return m_EntityID; }

		bool operator==(const Entity& other) const
		{
			return m_EntityID == other.m_EntityID && m_Scene == other.m_Scene;
		}
		
		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity m_EntityID = entt::null;
		Scene* m_Scene = nullptr;
	};

}
