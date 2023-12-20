// hierarchypanel.h

#pragma once

#include "Panel.h"
#include "../smolEngine/GameObject.h" // Include the GameObject header here

class Editor;

class HierarchyPanel : public Panel
{
public:
    HierarchyPanel(Editor* instance);
    virtual ~HierarchyPanel();

    void Draw() override;

    // Function to update the list of game objects
    void UpdateGameObjects(const std::vector<GameObject>& objects);

    // Function to get the ID of the selected game object
    int GetSelectedObjectId() const { return selectedObjectId; };

private:
    std::vector<GameObject> gameObjects; // Store game objects in the panel
    int selectedObjectId; // Store the ID of the selected game object (-1 for none selected)
};
