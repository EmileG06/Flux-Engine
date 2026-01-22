#include "SceneHierarchyPanel.h"

#include <imgui/imgui_internal.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Editor/Widgets/Widgets.h"

namespace Flux {

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		DrawSceneHierarchy();
		DrawProperties();
	}

	void SceneHierarchyPanel::DrawSceneHierarchy()
	{
		ImGui::Begin("Scene Hierarchy");

		for (auto entityID : m_Context->m_Registry.view<entt::entity>())
		{
			Entity entity = { entityID, m_Context.get() };
			DrawEntityNode(entity);
		}

		if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
			m_SelectionContext = {};

		if (ImGui::BeginPopupContextWindow("", ImGuiMouseButton_Right, false))
		{
			if (ImGui::MenuItem("New Entity"))
				m_SelectionContext = m_Context->CreateEntity("Entity");

			ImGui::EndPopup();
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawProperties()
	{
		ImGui::Begin("Properties");

		if (m_SelectionContext)
		{
			DrawEntityComponents(m_SelectionContext);

			if (ImGui::BeginPopupContextWindow("", ImGuiMouseButton_Right, false))
			{
				if (ImGui::BeginMenu("Add Component"))
				{
					if (ImGui::MenuItem("Camera"))
					{
						m_SelectionContext.AddComponent<CameraComponent>();
						ImGui::CloseCurrentPopup();
					}

					if (ImGui::BeginMenu("Mesh"))
					{
						if (ImGui::MenuItem("Empty"))
						{
							// TODO: Implement this
							ImGui::CloseCurrentPopup();
						}

						if (ImGui::MenuItem("Cube"))
						{
							m_SelectionContext.AddComponent<MeshComponent>(AssetManager::GetCube());
							ImGui::CloseCurrentPopup();
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Native Script"))
					{
						if (ImGui::MenuItem("Camera Controller"))
						{
							m_SelectionContext.AddComponent<NativeScriptComponent>().Bind<CameraController>();
							ImGui::CloseCurrentPopup();
						}

						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}

				ImGui::EndPopup();
			}
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_OpenOnArrow : 0) | ImGuiTreeNodeFlags_Selected;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			m_SelectionContext = entity;

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags childFlags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool childOpened = ImGui::TreeNodeEx((void*)309485, childFlags, tag.c_str());
			if (childOpened)
				ImGui::TreePop();

			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			if (m_SelectionContext == entity)
				m_SelectionContext = {};

			m_Context->DestroyEntity(entity);
		}
	}

	void SceneHierarchyPanel::DrawEntityComponents(Entity entity)
	{
		DrawComponent<TagComponent>("Tag Component", entity, [](TagComponent& component)
			{
				auto& tag = component.Tag;

				char buffer[256] = {};
				std::strncpy(buffer, tag.c_str(), sizeof(buffer) - 1);

				if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
					tag = std::string(buffer);
			});

		DrawComponent<TransformComponent>("Transform Component", entity, [](TransformComponent& component)
			{
				Widgets::DrawVec3("Position", component.Translation, 0.0f);

				glm::vec3 rotation = glm::degrees(component.Rotation);
				Widgets::DrawVec3("Rotation", rotation, 0.0f);
				component.Rotation = glm::radians(rotation);

				Widgets::DrawVec3("Scale", component.Scale, 1.0f);
			});

		DrawComponent<CameraComponent>("Camera Component", entity, [](CameraComponent& component)
			{
				ImGui::Checkbox("Main Camera", &component.MainCamera);
			});

		DrawComponent<MeshComponent>("Mesh Component", entity, [](MeshComponent& component)
			{
			});
	}

}
