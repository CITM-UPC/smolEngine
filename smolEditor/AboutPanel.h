#pragma once

#include "Panel.h"

class AboutPanel : public Panel
{
public:
	AboutPanel(Editor* instance);
	virtual ~AboutPanel();

	void Draw() override;
};