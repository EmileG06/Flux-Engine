#pragma once

#include <Flux.h>

#include <imgui/imgui.h>

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

		template <typename T>
		void DrawComponent(const std::string& label, Entity entity, const std::function<void(T&)>& func)
		{
			constexpr ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

			if (entity.HasComponent<T>())
			{
				bool opened = ImGui::TreeNodeEx((void*)(typeid(T).hash_code() + (uint32_t)entity), treeNodeFlags, label.c_str());

				bool componentDeleted = false;
				if (!std::is_same_v<T, TagComponent>)
				{
					if (ImGui::BeginPopupContextItem())
					{
						if (ImGui::MenuItem("Delete"))
							componentDeleted = true;

						ImGui::EndPopup();
					}
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
