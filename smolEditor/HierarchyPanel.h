// hierarchypanel.h

#pragma once

#include "Panel.h"
#include "../smolEngine/GameObject.h"

class Editor;

class HierarchyPanel : public Panel
{
public:
    HierarchyPanel(Editor* instance);
    virtual ~HierarchyPanel();

    void Draw() override;

    
    void UpdateGameObjects(const std::vector<GameObject>& objects);

    
    int GetSelectedObjectId() const { return selectedObjectId; };

private:
    std::vector<GameObject> gameObjects; 
    int selectedObjectId; 
};
