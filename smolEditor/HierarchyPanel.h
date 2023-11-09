#pragma once

#include "Panel.h"

class Editor;

class HierarchyPanel : public Panel
{
public:
	HierarchyPanel(Editor* instance);
	virtual ~HierarchyPanel();

	void Draw() override;
};