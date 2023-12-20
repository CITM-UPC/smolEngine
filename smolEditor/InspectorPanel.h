// inspectorPanel.h

#pragma once

#include "Panel.h"
#include "../smolEngine/GameObject.h" 

class Editor;

class InspectorPanel : public Panel
{
public:
    InspectorPanel(Editor* instance);
    virtual ~InspectorPanel();

    void Update() override;
    void Draw() override;    

private:
    
};
