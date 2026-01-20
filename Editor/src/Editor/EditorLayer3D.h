#pragma once

#include <Flux.h>

namespace Flux {

	class EditorLayer3D : public Layer
	{
	public:
		EditorLayer3D();
		virtual ~EditorLayer3D();

		void OnAttach() override;
		void OnDetach() override;

		void OnEvent(Event& e) override;
		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;

	private:
		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 1280.0f, 720.0f };
		bool m_ViewportFocused = false;

		PerspectiveCameraController m_EditorCamera;

		Ref<Scene> m_ActiveScene;
		Entity m_CubeEntity;
	};

}
