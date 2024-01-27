#pragma once

#include "GraphicObject.h"
#include "Defs.h"
#include "Mesh.h"
#include "Ray.h"
#include "glmath.h"
#include "Triangle.h"
#include "Color.h"
#include "WwiseUtils.h"
#include "SDL2/SDL.h"


class GameObject
{
public:

	//comment
	GameObject();
	GameObject(const std::string& n);
	GameObject(const std::string& n, bool StaticObject);
	GameObject(const std::string& path, const std::string& n, bool StaticObject);
	~GameObject();

	//uncomment
	//GameObject();
	//GameObject(const std::string& n, AkUniqueID soundEventID, bool StaticObject);
	//GameObject(const std::string& path, const std::string& n, AkUniqueID soundEventID, bool StaticObject);


	void LoadMesh(const std::string& path);
	void Draw();
	void Rotate(double rads, const dvec3& axis);
	void Move(const dvec3& displacement);
	void Scale(const dvec3& s);
	void Update();
	//move  and sound
	void StartMoving(const dvec3& startPos, const dvec3& endPos, float duration);
	void UpdateSoundPosition();

	const char* getName() { return name.c_str(); }
	unsigned int getID() const { return id; }
	bool GetSelected() { return isSelected; }
	bool GetStaticObject() { return StaticObject; }
	BoundingBox GetBoundingBox() { return boundingBox; }
	void SetSelected(bool selected) { 
		isSelected = selected;
	}

	bool Intersects(const Ray& ray, float& outDistance);
	bool RayIntersectsTriangle(const Ray& ray, const Triangle& triangle, float& outDistance);

private:

	//sound
	//uncomment
	//AkGameObjectID akGameObjectID;
	//static AkGameObjectID GenerateUniqueAkGameObjectID() {
	//	static AkGameObjectID nextID = 1; // start in 1, 0 is for the listener by default
	//	return nextID++;
	//}
	//void InitializeSound(AkUniqueID soundEventID);
	

	std::vector <BoundingBox> dividedMesh;
	BoundingBox boundingBox; 

	unsigned int id;

	std::string name;
	std::shared_ptr<GraphicObject> root;
	bool isSelected = false;

	//move
	dvec3 startPos;
	dvec3 endPos;
	dvec3 direction;
	double speed = 0.01;
	dvec3 currentPosition;
	dvec3 previousPosition;
	bool isMoving;
	bool movingTowardsEndPos = true;
	bool StaticObject;

	
};

//unsigned int GameObject::lastId;
