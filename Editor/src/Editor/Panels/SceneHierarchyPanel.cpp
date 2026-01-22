#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
#pragma region Scene Hierarchy

		ImGui::Begin("Scene Hierarchy");
		
		for (auto entityID : m_Context->m_Registry.view<entt::entity>())
		{
			Entity entity = { entityID, m_Context.get() };
			DrawEntityNode(entity);
		}

		if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
			m_SelectionContext = {};
		
		ImGui::End();

#pragma endregion

#pragma region Properties

		ImGui::Begin("Properties");

		if (m_SelectionContext)
			DrawComponents(m_SelectionContext);

		ImGui::End();

#pragma endregion
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_OpenOnArrow : 0) | ImGuiTreeNodeFlags_Selected;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		{
			if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
				m_SelectionContext = entity;

			if (opened)
				ImGui::TreePop();
		}
	}

#pragma region Component Widgets

	static void DrawVec3Widget(const std::string& label, glm::vec3& value, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);

		// Label Column
		ImGui::SetColumnWidth(0, columnWidth);

		ImGui::Text(label.c_str());

		// Vec3 Column
		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.9f, 0.25f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("X", buttonSize))
			value.x = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();

		ImGui::DragFloat("##x", &value.x, 0.1f, 0.0f, 0.0f, "%.2f");

		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.2f, 0.7f, 0.3f, 1.0f });
		if (ImGui::Button("Y", buttonSize))
			value.y = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();

		ImGui::DragFloat("##y", &value.y, 0.1f, 0.0f, 0.0f, "%.2f");

		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.25f, 0.85f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("Z", buttonSize))
			value.z = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();

		ImGui::DragFloat("##z", &value.z, 0.1f, 0.0f, 0.0f, "%.2f");

		ImGui::PopItemWidth();
		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

#pragma endregion

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TagComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Tag Component"))
			{
				auto& tag = entity.GetComponent<TagComponent>().Tag;

				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strcpy_s(buffer, sizeof(buffer), tag.c_str());

				if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
					tag = std::string(buffer);

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform Component"))
			{
				auto& transform = entity.GetComponent<TransformComponent>();

				DrawVec3Widget("Position", transform.Translation, 0.0f);

				glm::vec3 rotation = glm::degrees(transform.Rotation);
				DrawVec3Widget("Rotation", rotation, 0.0f);
				transform.Rotation = glm::radians(rotation);

				DrawVec3Widget("Scale", transform.Scale, 1.0f);

				ImGui::TreePop();
			}
		}
	}

}
