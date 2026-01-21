#include "EditorLayer.h"

#include <Flux/Renderer/RenderCommand.h>
#include <Flux/Renderer/Renderer3D.h>
#include <ImGui/ImGui.h>

namespace Flux {

	EditorLayer::EditorLayer()
	{
		Flux::FramebufferSpecification fbSpec;
		fbSpec.Width = 1920;
		fbSpec.Height = 1080;
		m_Framebuffer = Flux::Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();

		std::vector<Vertex3D> vertices = {
			{ { -0.5f, -0.5f,  0.5f } },
			{ {  0.5f, -0.5f,  0.5f } },
			{ {  0.5f,  0.5f,  0.5f } },
			{ { -0.5f,  0.5f,  0.5f } },
			{ { -0.5f, -0.5f, -0.5f } },
			{ {  0.5f, -0.5f, -0.5f } },
			{ {  0.5f,  0.5f, -0.5f } },
			{ { -0.5f,  0.5f, -0.5f } }
		};

		std::vector<uint32_t> indices = {
			0, 1, 2,
			2, 3, 0,
			1, 5, 6,
			6, 2, 1,
			5, 4, 7,
			7, 6, 5,
			4, 0, 3,
			3, 7, 4,
			3, 2, 6,
			6, 7, 3,
			4, 5, 1,
			1, 0, 4
		};

		m_CubeEntity = m_ActiveScene->CreateEntity("Cube");
		m_CubeEntity.AddComponent<MeshComponent>(AssetManager::CreateMesh(vertices, indices));

		class CameraController : public ScriptableEntity
		{
		protected:
			void OnCreate() override
			{
			}

			void OnDestroy() override
			{
			}

			void OnUpdate(Timestep ts) override
			{
				auto& cameraComp = GetComponent<CameraComponent>();
				float movementOffset = m_CameraSpeed * ts.GetSeconds();

				if (Input::IsKeyPressed(FX_KEY_D))
					cameraComp.Position -= cameraComp.ViewRight * movementOffset;
				else if (Input::IsKeyPressed(FX_KEY_A))
					cameraComp.Position += cameraComp.ViewRight * movementOffset;

				if (Input::IsKeyPressed(FX_KEY_W))
					cameraComp.Position += cameraComp.ViewForward * movementOffset;
				else if (Input::IsKeyPressed(FX_KEY_S))
					cameraComp.Position -= cameraComp.ViewForward * movementOffset;

				if (Input::IsKeyPressed(FX_KEY_SPACE))
					cameraComp.Position += cameraComp.ViewUp * movementOffset;
				else if (Input::IsKeyPressed(FX_KEY_Q))
					cameraComp.Position -= cameraComp.ViewUp * movementOffset;

				cameraComp.Update();
			}

		private:
			float m_CameraSpeed = 2.5f;
		};

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<CameraComponent>(glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f));
		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		
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
		m_ActiveScene->OnEvent(event);
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		m_Framebuffer->Bind();

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		if (m_CameraEntity)
		{
			auto& cameraComp = m_CameraEntity.GetComponent<CameraComponent>();

			Renderer3D::BeginScene(cameraComp.GetViewProjectionMatrix());

			m_ActiveScene->OnUpdate(ts);

			Renderer3D::EndScene();
		}

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
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
