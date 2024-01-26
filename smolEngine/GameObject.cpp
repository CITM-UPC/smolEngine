#include "GameObject.h"

#include <glm/glm.hpp>
#include "Mesh.h"


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
