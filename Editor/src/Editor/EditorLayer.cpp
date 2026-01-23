#include "EditorLayer.h"

#include <Flux/Renderer/RenderCommand.h>
#include <Flux/Renderer/Renderer3D.h>
#include <Flux/Scripts/CameraController.h>

#include <ImGui/ImGui.h>

namespace Flux {

	EditorLayer::EditorLayer()
		: m_EditorCamera(45.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f)
	{
		Flux::FramebufferSpecification fbSpec;
		fbSpec.Width = 1920;
		fbSpec.Height = 1080;
		m_Framebuffer = Flux::Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();

		auto cubeEntity = m_ActiveScene->CreateEntity("Cube");
		cubeEntity.AddComponent<MeshComponent>(AssetManager::GetCube());
		
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnEvent(Event& event)
	{
		if (m_ViewportFocused)
			m_EditorCamera.OnEvent(event);

		m_ActiveScene->OnEvent(event);
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		if (m_ViewportFocused)
			m_EditorCamera.OnUpdate(ts);

		m_Framebuffer->Bind();

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool dockspaceOpen = true;
		static bool optFullscreen = true;
		static ImGuiDockNodeFlags dockFlags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (optFullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			windowFlags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::Begin("Dockspace", &dockspaceOpen, windowFlags);
		ImGui::PopStyleVar();

		if (optFullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowMinSize.x = 385.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspaceID, { 0.0f, 0.0f }, dockFlags);
		}
		style.WindowMinSize.x = 32.0f;

#pragma region Toolbar

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) Flux::Application::Get().Stop();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

#pragma endregion

#pragma region Panels

		m_SceneHierarchyPanel.OnImGuiRender();

#pragma endregion

#pragma region Viewport

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::Begin("Viewport");
		{
			m_ViewportFocused = ImGui::IsWindowFocused();
			Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused);

			glm::vec2 viewportPanelSize = glm::vec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
			if (m_ViewportSize != viewportPanelSize)
			{
				m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
				float aspectRatio = viewportPanelSize.x / viewportPanelSize.y;
				m_ActiveScene->OnViewportResized((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
				m_EditorCamera.SetViewportSize(viewportPanelSize.x, viewportPanelSize.y);
				m_ViewportSize = viewportPanelSize;
			}
			uint32_t textureID = m_Framebuffer->GetColorAttachmentID();
			ImGui::Image((void*)textureID, { m_ViewportSize.x, m_ViewportSize.y }, { 0, 1 }, { 1, 0 });
			ImGui::End();
		}
		ImGui::PopStyleVar();

#pragma endregion

		ImGui::End();
	}

}
