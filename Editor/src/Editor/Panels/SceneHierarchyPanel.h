#pragma once

#include <Flux.h>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace Flux {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

	private:
		void DrawSceneHierarchy();
		void DrawProperties();

		void DrawEntityNode(Entity entity);
		void DrawEntityComponents(Entity entity);

		template <typename T, typename UIFunc>
		void DrawComponent(const std::string& label, Entity entity, UIFunc func)
		{
			constexpr ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding;

			if (entity.HasComponent<T>())
			{
				ImVec2 contentRegion = ImGui::GetContentRegionAvail();

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4.0f, 4.0f });
				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

				ImGui::Separator();
				bool opened = ImGui::TreeNodeEx((void*)(typeid(T).hash_code() + (uint32_t)entity), treeNodeFlags, label.c_str());

				ImGui::PopStyleVar();

				ImGui::SameLine(contentRegion.x - lineHeight * 0.5f);
				if (ImGui::Button("+", { lineHeight, lineHeight }))
					ImGui::OpenPopup("##ComponentSettings");


				bool componentDeleted = false;
				if (ImGui::BeginPopup("##ComponentSettings"))
				{
					if (ImGui::MenuItem("Delete"))
						componentDeleted = true;

					ImGui::EndPopup();
				}

				if (opened)
				{
					func(entity.GetComponent<T>());
					ImGui::TreePop();
				}

				if (componentDeleted)
					entity.RemoveComponent<T>();
			}
		}

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}
