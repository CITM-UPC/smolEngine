#pragma once

#include "GraphicObject.h"
#include "Defs.h"
#include "Mesh.h"
#include "Ray.h"
#include "glmath.h"
#include "Triangle.h"
#include "Color.h"

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
	void Move(const dvec3& displacement);
	void Scale(const dvec3& s);

	const char* getName() { return name.c_str(); }
	void setName(const char* n) { name = n; }
	unsigned int getID() const { return id; }
	bool GetSelected() { return isSelected; }
	BoundingBox GetBoundingBox() { return boundingBox; }
	void SetSelected(bool selected) { 
		isSelected = selected;
	}

	bool Intersects(const Ray& ray, float& outDistance);
	bool RayIntersectsTriangle(const Ray& ray, const Triangle& triangle, float& outDistance);

	/*void generateId()
	{
		lastId++;
		id = lastId;
	}*/
public:

	/*unsigned int id = 0;
	static unsigned int lastId;*/

private:

	std::vector <BoundingBox> dividedMesh;
	BoundingBox boundingBox; 

	unsigned int id;

	std::string name;
	std::shared_ptr<GraphicObject> root;
	bool isSelected = false;

};

//unsigned int GameObject::lastId;
