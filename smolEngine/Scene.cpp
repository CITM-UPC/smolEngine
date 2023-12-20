#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
    Clear();
}

std::shared_ptr<GameObject> Scene::AddGameObject(const std::string& name) {
    auto gameObject = std::make_shared<GameObject>(name);
    gameObjects.push_back(gameObject);
    return gameObject;
}

bool Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject) {
    auto it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
        return true;
    }
    return false;
}

const std::vector<std::shared_ptr<GameObject>>& Scene::GetGameObjects() const {
    return gameObjects;
}

void Scene::Clear() {
    gameObjects.clear();
}
