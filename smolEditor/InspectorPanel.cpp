#include "InspectorPanel.h"
#include "InspectorPanel.h"
#include <imgui.h>
#include "../smolEngine/Application.h"
#include "../smolEngine/Render.h"
#include "Editor.h"

InspectorPanel::InspectorPanel(Editor* instance) : Panel("Hierarchy", instance)
{
}

InspectorPanel::~InspectorPanel()
{
}

void InspectorPanel::Update() {
}

void InspectorPanel::Draw()
{
	vec3f oldPosition = vec3f();
	vec3f Position = vec3f();

	vec3f oldRotation = vec3f();
	vec3f Rotation = vec3f();
	dvec3 actualAxis = dvec3();

	vec3f oldScale = vec3f();
	vec3f Scale = vec3f();

    ImGui::Begin("Inspector");

    auto selectedObject = app->render->GetCurrentSelectedObject();
    if (selectedObject != nullptr) {
        const char* entName = selectedObject->getName();
        std::string edit = entName;

        // Display Object Name
        ImGui::InputText("Name", (char*)edit.c_str(), 64);
        if (strcmp(edit.c_str(), entName) != 0)
            selectedObject->setName(edit.c_str());

        if (ImGui::CollapsingHeader("Transform"))
        {

			// POSITION
            ImGui::PushID("Position");
			ImGui::PushID("Position");

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 100.0f);
			ImGui::Text("Position");
			ImGui::NextColumn();

			ImGui::PushItemWidth(ImGui::CalcItemWidth());
			ImGui::PushItemWidth(ImGui::CalcItemWidth());
			ImGui::PushItemWidth(ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 10 });

			ImVec2 buttonSize = { 20, 20 };

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
			{
				Position.x = 0;
			}


			ImGui::SameLine();
			ImGui::DragFloat("##X", &Position.x, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize))
			{
				Position.y = 0;
			}


			ImGui::SameLine();
			ImGui::DragFloat("##Y", &Position.y, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			if (ImGui::Button("Z", buttonSize))
			{
				Position.z = 0;
			}

			ImGui::SameLine();
			ImGui::DragFloat("##Z", &Position.z, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::Columns(1);

			ImGui::PopID();
            ImGui::PopID();

			// ROTATION
			ImGui::PushID("Rotation");
			ImGui::PushID("Rotation");

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 100.0f);
			ImGui::Text("Rotation");
			ImGui::NextColumn();

			ImGui::PushItemWidth(ImGui::CalcItemWidth());
			ImGui::PushItemWidth(ImGui::CalcItemWidth());
			ImGui::PushItemWidth(ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 10 });

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
			{
				Rotation.x = 0;
				actualAxis = dvec3(1, 0, 0);
			}

			ImGui::SameLine();
			if (ImGui::DragFloat("##X", &Rotation.x, 0.1f, 0.0f, 0.0f, "%.2f"))
				actualAxis = dvec3(1, 0, 0);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize))
			{
				Rotation.y = 0;
				actualAxis = dvec3(0, 1, 0);
			}


			ImGui::SameLine();
			if(ImGui::DragFloat("##Y", &Rotation.y, 0.1f, 0.0f, 0.0f, "%.2f"))
				actualAxis = dvec3(0, 1, 0);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			if (ImGui::Button("Z", buttonSize))
			{
				Rotation.z = 0;
				actualAxis = dvec3(0, 0, 1);
			}

			ImGui::SameLine();
			if(ImGui::DragFloat("##Z", &Rotation.z, 0.1f, 0.0f, 0.0f, "%.2f"))
				actualAxis = dvec3(0, 0, 1);
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::Columns(1);

			ImGui::PopID();
			ImGui::PopID();

			// SCALE
			ImGui::PushID("Scale");
			ImGui::PushID("Scale");

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 100.0f);
			ImGui::Text("Scale");
			ImGui::NextColumn();

			ImGui::PushItemWidth(ImGui::CalcItemWidth());
			ImGui::PushItemWidth(ImGui::CalcItemWidth());
			ImGui::PushItemWidth(ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 10 });

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
			{
				Scale.x = 1;
			}


			ImGui::SameLine();
			ImGui::DragFloat("##X", &Scale.x, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize))
			{
				Scale.y = 1;
			}


			ImGui::SameLine();
			ImGui::DragFloat("##Y", &Scale.y, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			if (ImGui::Button("Z", buttonSize))
			{
				Scale.z = 1;
			}

			ImGui::SameLine();
			ImGui::DragFloat("##Z", &Scale.z, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::Columns(1);

			ImGui::PopID();
			ImGui::PopID();




			if (Position != oldPosition)
			{
				selectedObject->Move(Position);
			}
			//Este hay que cambiarlo un poco
			if (Rotation.x != oldRotation.x)
			{
				selectedObject->Rotate(Rotation.x, actualAxis);
			}
			//Este hay que cambiarlo un poco
			if (Rotation.y != oldRotation.y)
			{
				selectedObject->Rotate(Rotation.y, actualAxis);
			}
			//Este hay que cambiarlo un poco
			if (Rotation.z != oldRotation.z)
			{
				selectedObject->Rotate(Rotation.z, actualAxis);
			}
			if (Scale != oldScale)
			{
				selectedObject->Scale(Scale);
			}
        }

        int triangles = selectedObject->GetBoundingBox().triangles.size();
        ImGui::Text("Num of triangles: %i", triangles);

        //ImGui::InputFloat3("Edit Position", &position.x); // This will make position editable in UI
        //selectedObject->SetPosition(position); // Update the position of the object
    }

    ImGui::End();
}