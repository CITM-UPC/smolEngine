#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"

class Scene {
public:
    Scene();
    ~Scene();

    // Add a new GameObject to the scene
    std::shared_ptr<GameObject> AddGameObject(const std::string& name);

    // Remove a GameObject from the scene
    bool RemoveGameObject(std::shared_ptr<GameObject> gameObject);

    // Get all GameObjects in the scene
    const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() const;

    // Clear the scene
    void Clear();

private:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
};

