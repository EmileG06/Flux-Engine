#pragma once

#include "Flux/Core/Timestep.h"
#include "Flux/Events/Event.h"

namespace Flux {

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnEvent(Event& e) {}
		virtual void OnUpdate(Timestep ts) {}
	};

}
