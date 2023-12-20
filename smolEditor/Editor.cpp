#include "Editor.h"
#include "../smolEngine/Defs.h"

Editor::Editor(bool startEnabled) : Module(startEnabled)
{
}

// Destructor
Editor::~Editor()
{}

// Called before the first frame
bool Editor::Start()
{
	//LOG("render start");
	about = std::make_unique<AboutPanel>(this);
	hierarchy = std::make_unique<HierarchyPanel>(this);
	inspector = std::make_unique<InspectorPanel>(this);

	panels.push_back(about.get());
	panels.push_back(hierarchy.get());
	panels.push_back(inspector.get());

	return true;
}

// Called each loop iteration
bool Editor::PreUpdate()
{

	return true;
}

bool Editor::Update(float dt)
{
	return true;
}

bool Editor::PostUpdate()
{
	return true;
}

bool Editor::OnRenderUI()
{
	for (auto const& panel : panels)
	{
		panel->Draw();
	}

	return true;
}

// Called before quitting
bool Editor::CleanUp()
{
	LOG("Destroying SDL render");

	return true;
}