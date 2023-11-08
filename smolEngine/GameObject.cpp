#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(const std::string& n)
{
	root = std::make_shared<GraphicObject>();
	name = n;
	//generateId();
}

GameObject::GameObject(const std::string& path, const std::string& n)
{
	root = std::make_shared<GraphicObject>();
	name = n;
	LoadMesh(path);
	//generateId();
}

GameObject::~GameObject()
{
}

void GameObject::LoadMesh(const std::string& path)
{
	static auto mesh_ptrs = Mesh::loadFromFile(path);
	GraphicObject object;
	for (auto const& mesh_ptr : mesh_ptrs)
	{
		GraphicObject mesh(mesh_ptr);
		object.addChild(std::move(mesh));
	}
	root->addChild(std::move(object));
}

void GameObject::Draw()
{
	if(root)
		root->paint();
}

void GameObject::Rotate(double rads, const dvec3& axis)
{
	root->rotate(rads, axis);
}
