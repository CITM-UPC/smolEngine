#pragma once

#include "GraphicObject.h"
#include "Defs.h"
#include "Mesh.h"

class GameObject
{
public:

	GameObject();
	GameObject(const std::string& n);
	GameObject(const std::string& path, const std::string& n);
	~GameObject();

	void LoadMesh(const std::string& path);

	void Draw();

	void Rotate(double rads, const dvec3& axis);

	/*void generateId()
	{
		lastId++;
		id = lastId;
	}*/
public:

	/*unsigned int id = 0;
	static unsigned int lastId;*/

private:

	std::string name;

	std::shared_ptr<GraphicObject> root;

};

//unsigned int GameObject::lastId;
