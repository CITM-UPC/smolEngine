#include "GameObject.h"

#include <glm/glm.hpp>
#include "glmath.h"
#include "Mesh.h"

GameObject::GameObject() : isMoving(false)
{
}


//comment

GameObject::GameObject(const std::string& n) : currentPosition(0.0, 0.0, 0.0), previousPosition(0.0, 0.0, 0.0), startPos(0.0, 0.0, 0.0), endPos(10.0, 0.0, 0.0), speed(0.1), isMoving(false), movingTowardsEndPos(true)
{
    root = std::make_shared<GraphicObject>();
    name = n;
}
GameObject::GameObject(const std::string& n, bool StaticObject) : currentPosition(0.0, 0.0, 0.0), previousPosition(0.0, 0.0, 0.0), startPos(0.0, 0.0, 0.0), endPos(10.0, 0.0, 0.0), speed(0.1), isMoving(false), movingTowardsEndPos(true)
{
    this->StaticObject = StaticObject;
	root = std::make_shared<GraphicObject>();
	name = n;
}

GameObject::GameObject(const std::string& path, const std::string& n, bool StaticObject) : currentPosition(0.0, 0.0, 0.0), previousPosition(0.0, 0.0, 0.0), startPos(0.0, 0.0, 0.0), endPos(10.0, 0.0, 0.0), speed(0.1), isMoving(false), movingTowardsEndPos(true)
{
    this->StaticObject = StaticObject;
	root = std::make_shared<GraphicObject>();
	name = n;
	LoadMesh(path);
}

//uncomment
//GameObject::GameObject(const std::string& n, AkUniqueID soundEventID, bool StaticObject) : isMoving(false)
//{
//    this->StaticObject = StaticObject;
//    root = std::make_shared<GraphicObject>();
//    name = n;
//
//    //if soundevent id is valid it register the game object in wwise and associates the event
//    if (soundEventID != AK_INVALID_UNIQUE_ID) {
//        InitializeSound(soundEventID);
//    }
//}
//
//GameObject::GameObject(const std::string& path, const std::string& n, AkUniqueID soundEventID, bool StaticObject) : isMoving(false)
//{
//    this->StaticObject = StaticObject;
//    root = std::make_shared<GraphicObject>();
//    LoadMesh(path);
//    name = n;
//
//    //if soundevent id is valid it register the game object in wwise and associates the event
//    if (soundEventID != AK_INVALID_UNIQUE_ID) {
//        InitializeSound(soundEventID);
//    }    
//}

GameObject::~GameObject()
{
    //uncomment
    //AK::SoundEngine::UnregisterGameObj(akGameObjectID);
}

void GameObject::LoadMesh(const std::string& path)
{
    //breakpoint
	PTRMeshData temp = Mesh::loadFromFile(path);
	
	auto mesh_ptrs = temp.mesh_ptrs;

	GraphicObject object;
	for (auto const& mesh_ptr : mesh_ptrs)
	{
		GraphicObject mesh(mesh_ptr);
		object.addChild(std::move(mesh));
	}
    //move the object to its location, it was painful
    object.rotate(135 * 0.0174533, dvec3(1, 0, 0));

    //creates meshsegments in the gameobject for the raycast
	this->dividedMesh = Mesh::CreateMeshSegments(50, temp.triangles);

    //sets the gameobject bounding box
    this->boundingBox.SetTriangleVector(temp.triangles);
    this->boundingBox.CalculateBounds(true);

	root->addChild(std::move(object));
}

void::GameObject::Update() {

    if (isMoving) {
        // Determina el destino actual basado en la dirección del movimiento
        dvec3 targetPos = movingTowardsEndPos ? endPos : startPos;

        // Calcula la dirección hacia el objetivo actual
        dvec3 moveDirection = glm::normalize(targetPos - currentPosition);

        // Mueve el objeto en la dirección actual a una velocidad constante
        currentPosition += moveDirection * speed;

        // Verifica si el objeto está cerca del destino
        if (glm::distance(currentPosition, targetPos) < speed) {
            // Se ha alcanzado o pasado el destino; ajusta la posición al destino para evitar saltos
            currentPosition = targetPos;

            // Invierte la dirección del movimiento para el próximo ciclo
            movingTowardsEndPos = !movingTowardsEndPos;
        }

        // Aplica la nueva posición
        Move(currentPosition - previousPosition);
        previousPosition = currentPosition;
    }

    //uncomment
    //UpdateSoundPosition();

}

void GameObject::Draw()
{
    root->paint();

    /*for (auto const& bBox : dividedMesh)
    {
        bBox.Draw();
    }*/

    //draws bounding box, should be dependent on the debug
    if (isSelected) {
        boundingBox.SetBoundingBoxColor(Green);
        }
    else {
        boundingBox.SetBoundingBoxColor(White);
    }

    boundingBox.Draw();
}

void GameObject::StartMoving(const dvec3& startPos, const dvec3& endPos, float duration) {
    this->startPos = startPos;
    this->endPos = endPos;
    this->isMoving = true;
    this->currentPosition = startPos;
}

void GameObject::Rotate(double rads, const dvec3& axis)
{
	root->rotate(rads, axis);
}

void GameObject::Move(const dvec3& displacement)
{
    root->move(displacement);
}

void GameObject::Scale(const dvec3& s)
{
    root->scale(s);
}

bool GameObject::Intersects(const Ray& ray, float& outDistance) {
    bool hit = false;
    outDistance = std::numeric_limits<float>::max();

    // Iterate over each bounding box in the BVH
    for (const BoundingBox& segment : this->dividedMesh) {
        if (segment.Intersects(ray)) {
            // If the ray intersects the bounding box, check for intersection with each triangle in this segment
            for (const Triangle& triangle : segment.triangles) {
                float distance;
                if (RayIntersectsTriangle(ray, triangle, distance)) {
                    if (distance < outDistance) {
                        outDistance = distance;
                        hit = true;
                    }
                }
            }
        }
    }

    return hit;
}

bool GameObject::RayIntersectsTriangle(const Ray& ray, const Triangle& triangle, float& outDistance) {
    const float EPSILON = 0.0000001f;
    vec3 vertex0 = triangle.GetVertex0();
    vec3 vertex1 = triangle.GetVertex1();
    vec3 vertex2 = triangle.GetVertex2();
    vec3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = cross(ray.GetDirection(), edge2);
    a = dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return false;    // Ray is parallel to triangle
    f = 1.0 / a;
    s = ray.GetOrigin() - vertex0;
    u = f * dot(s, h);
    if (u < 0.0 || u > 1.0)
        return false;
    q = cross(s, edge1);
    v = f * dot(ray.GetDirection(), q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    // Compute where the intersection point is on the line
    float t = f * dot(edge2, q);
    if (t > EPSILON) {
        outDistance = t;
        return true;
    }
    else {
        return false;
    }
}

//uncomment
//void GameObject::InitializeSound(AkUniqueID soundEventID) {
//    if (soundEventID != AK_INVALID_UNIQUE_ID) {
//        // Suponiendo que GenerateUniqueAkGameObjectID es una función que has definido
//        // para generar IDs únicos para tus objetos de juego.
//        akGameObjectID = GenerateUniqueAkGameObjectID();
//        AK::SoundEngine::RegisterGameObj(akGameObjectID, name.c_str());
//        AK::SoundEngine::PostEvent(soundEventID, akGameObjectID);
//    }
//}
//
////sound update
//void GameObject::UpdateSoundPosition() {
//    AkSoundPosition soundPos;
//
//    soundPos.SetPosition(currentPosition.x, currentPosition.y, currentPosition.z);
//    soundPos.SetOrientation(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
//
//    AK::SoundEngine::SetPosition(akGameObjectID, soundPos);
//}
