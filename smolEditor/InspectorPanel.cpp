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
    ImGui::Begin("Inspector");

    auto selectedObject = app->render->GetCurrentSelectedObject();
    if (selectedObject != nullptr) {
        // Display Object Name
        ImGui::Text("Name: %s", selectedObject->getName());

        int triangles = selectedObject->GetBoundingBox().triangles.size();
        ImGui::Text("Num of triangles: %i", triangles);

        //ImGui::InputFloat3("Edit Position", &position.x); // This will make position editable in UI
        //selectedObject->SetPosition(position); // Update the position of the object
    }

    ImGui::End();
}