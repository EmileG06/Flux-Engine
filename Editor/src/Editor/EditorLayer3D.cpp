#include "EditorLayer3D.h"

#include <Flux/Renderer/RenderCommand.h>
#include <Flux/Renderer/Renderer3D.h>
#include <ImGui/ImGui.h>

namespace Flux {

	EditorLayer3D::EditorLayer3D()
		: m_Camera(45.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f)
	{
		Flux::FramebufferSpecification fbSpec;
		fbSpec.Width = 1920;
		fbSpec.Height = 1080;
		m_Framebuffer = Flux::Framebuffer::Create(fbSpec);
	}

	EditorLayer3D::~EditorLayer3D()
	{
	}

	void EditorLayer3D::OnAttach()
	{
	}

	void EditorLayer3D::OnDetach()
	{
	}

	void EditorLayer3D::OnEvent(Event& event)
	{
	}

	void EditorLayer3D::OnUpdate(Timestep ts)
	{
		Renderer2D::ResetStats();

		m_Framebuffer->Bind();

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		Renderer3D::BeginScene(m_Camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_CubePosition)
			* glm::mat4_cast(glm::quat(glm::radians(m_CubeRotation)))
			* glm::scale(glm::mat4(1.0f), { 1.0f, 1.0f, 1.0f });

		Renderer3D::DrawCube(transform, m_CubeColor);

		Renderer3D::EndScene();

		m_Framebuffer->Unbind();
	}

	void EditorLayer3D::OnImGuiRender()
	{
#pragma region ImGuiDockspace
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
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspaceID, { 0.0f, 0.0f }, dockFlags);
		}
#pragma endregion

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) Flux::Application::Get().Stop();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if (ImGui::Begin("Settings"))
		{
			ImGui::DragFloat3("Cube Position", glm::value_ptr(m_CubePosition), 0.05f, -10.0f, 10.0f);
			ImGui::DragFloat3("Cube Rotation", glm::value_ptr(m_CubeRotation), 1.0f, -180.0f, 180.0f);
			ImGui::ColorEdit4("Cube Color", glm::value_ptr(m_CubeColor));

			ImGui::End();
		}

		if (ImGui::Begin("Statistics"))
		{
			const auto& lastFrame = Renderer2D::GetStats();

			ImGui::Text("Draw Calls: %u", lastFrame.DrawCalls);
			ImGui::Text("Quads: %u", lastFrame.QuadCount);
			ImGui::Text("Vertices: %u", lastFrame.GetTotalVertexCount());
			ImGui::Text("Indices: %u", lastFrame.GetTotalIndexCount());

			ImGui::Separator();

			const auto& position = m_Camera.GetPosition();
			ImGui::Text("Camera Position: %.3f, %.3f, %.3f", position.x, position.y, position.z);

			const auto& rotation = m_Camera.GetRotation();
			ImGui::Text("Camera Rotation: %.3f, %.3f, %.3f", rotation.x, rotation.y, rotation.z);

			const auto& forward = m_Camera.GetViewForward();
			ImGui::Text("Camera Forward: %.3f, %.3f, %.3f", forward.x, forward.y, forward.z);

			const auto& right = m_Camera.GetViewRight();
			ImGui::Text("Camera Right: %.3f, %.3f, %.3f", right.x, right.y, right.z);

			const auto& up = m_Camera.GetViewUp();
			ImGui::Text("Camera Up: %.3f, %.3f, %.3f", up.x, up.y, up.z);

			ImGui::End();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		if (ImGui::Begin("Viewport"))
		{
			glm::vec2 viewportPanelSize = glm::vec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
			if (m_ViewportSize != viewportPanelSize)
			{
				m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
				float aspectRatio = viewportPanelSize.x / viewportPanelSize.y;
				m_Camera.SetProjection(45.0f, aspectRatio, 0.1f, 1000.0f);
				m_ViewportSize = viewportPanelSize;
			}
			uint32_t textureID = m_Framebuffer->GetColorAttachmentID();
			ImGui::Image((void*)textureID, { m_ViewportSize.x, m_ViewportSize.y }, { 0, 1 }, { 1, 0 });
			ImGui::End();
		}
		ImGui::PopStyleVar();

		ImGui::End();
	}

}
