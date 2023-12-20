#include "HierarchyPanel.h"
#include <imgui.h>
#include "../smolEngine/Application.h"
#include "../smolEngine/Render.h"
#include "Editor.h"

HierarchyPanel::HierarchyPanel(Editor* instance) : Panel("Hierarchy", instance), selectedObjectId(-1) // Initialize selected object ID as -1 (none selected)
{
}

HierarchyPanel::~HierarchyPanel()
{
}

void HierarchyPanel::Draw()
{
	ImGui::Begin(name, &active);
	if (ImGui::BeginPopupContextWindow("Context Menu"))
	{
		if (ImGui::MenuItem("Create New Entity"))
		{
			app->render->AddGameObject("New Entity");
		}
		//TODO: Remove test
		/*if(ImGui::MenuItem("Create 2D tree"))
		{
			ResourceId tree = Wiwa::Resources::Load<Wiwa::Image>("resources/images/tree.png");
			Wiwa::Image* spr = Wiwa::Resources::GetResourceById<Wiwa::Image>(tree);
			Wiwa::Size2i size = spr->GetSize();
			EntityId EntityMyTree = entityManager.CreateEntity("Arbolsito rechulon");
			entityManager.AddComponent<Wiwa::Transform2D>(EntityMyTree, { {0,0},0.f,{1.0,1.0} });
			entityManager.AddComponent<Wiwa::Sprite>(EntityMyTree, { {256,256}, tree,{size.w / 4, size.h / 4, size.w / 2, size.h / 2} });
		}*/
		if (ImGui::BeginMenu("Primitives"))
		{
			if (ImGui::MenuItem("Draw cube"))
			{
				app->render->cubeTest();
			}
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}


	if(ImGui::Button("+"))
	{
		app->render->AddGameObject("New Entity");
	}

	float width = ImGui::GetWindowContentRegionWidth();
	int id = 0;
	for (auto const& object : app->render->objects)
	{
		ImGui::PushID(id++);
		if (ImGui::Selectable(object.get()->getName(), selectedObjectId == object.get()->getID(), ImGuiSelectableFlags_AllowDoubleClick))
		{
			// Handle object selection
			selectedObjectId = object.get()->getID();
			// You can perform further actions upon selection here
		}
		ImGui::PopID();
	}

	ImGui::End();
}

void HierarchyPanel::UpdateGameObjects(const std::vector<GameObject>& objects)
{
	gameObjects = objects; // Update the game objects displayed in the panel
}