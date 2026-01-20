#include "FXPch.h"
#include "Entity.h"

namespace Flux {



	Entity::Entity(entt::entity entityID, Scene* scene)
		: m_EntityID(entityID), m_Scene(scene)
	{
	}

	Entity::~Entity()
	{
	}

}
