#include "AboutPanel.h"

#include "imgui.h"

#include "../smolEngine/Application.h"

AboutPanel::AboutPanel(Editor* instance) : Panel("About", instance)
{
}

AboutPanel::~AboutPanel()
{
}

void AboutPanel::Draw()
{

	ImGui::Begin(name, &active);
	ImGui::Separator();
	ImGui::Text("smolEngine version: %s", app->GetVersion());
	ImGui::Text("Small engine for small games");
	ImGui::Text("By Alex Delgado & Pau Vives");
	ImGui::Separator();
	ImGui::Text("3rd party libraries used:");
	ImGui::BulletText("SDL");
	ImGui::BulletText("Glew");
	ImGui::BulletText("ImGui Docking-Experimental");
	ImGui::BulletText("GLM");
	ImGui::BulletText("Assimp");
	ImGui::BulletText("DevIL");
	ImGui::Separator();
	ImGui::Text("MIT License\n");
	ImGui::Text("Copyright (c) 2023 Faelion & PauVives");
	ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
	ImGui::Text("of this software and associated documentation files (the 'Software'), to deal");
	ImGui::Text("in the Software without restriction, including without limitation the rights");
	ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and/or sell");
	ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
	ImGui::Text("furnished to do so, subject to the following conditions:");
	ImGui::Text("The above copyright notice and this permission notice shall be included in all");
	ImGui::Text("copies or substantial portions of the Software.");
	ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
	ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
	ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE");
	ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
	ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
	ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
	ImGui::Text("SOFTWARE.");
	ImGui::End();
}
