#pragma once

#include "Flux/Core.h"
#include "Flux/Scene/Entity.h"

namespace Flux {

	class ScriptableEntity
	{
	public:
		template <typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	private:
		Entity m_Entity;

		friend class Scene;
	};

}
