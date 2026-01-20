#pragma once

#include <Flux.h>

#include "Panels/SceneHierarchyPanel.h"

namespace Flux {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnEvent(Event& e) override;
		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;

	private:
		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 1280.0f, 720.0f };
		bool m_ViewportFocused = false;

		Ref<Scene> m_ActiveScene;
		Entity m_CameraEntity;
		Entity m_CubeEntity;

		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}
