#pragma once

#include "Flux/Core.h"
#include "Flux/Core/Layer.h"
#include "Flux/Core/Timestep.h"

#include "Flux/Events/WindowEvents.h"
#include "Flux/Events/KeyEvents.h"
#include "Flux/Events/MouseEvents.h"

namespace Flux {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnEvent(Event& event) override;

		void Begin();
		void End();

		void BlockEvents(bool blockEvents) { m_BlockEvents = blockEvents; }

		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;

	private:
		bool m_BlockEvents = false;
	};

}
