#include "BoundingBox.h"

BoundingBox::BoundingBox() : minPoint(FLT_MAX), maxPoint(-FLT_MAX) {}

void BoundingBox::AddTriangle(const Triangle& triangle) {
    triangles.push_back(triangle);
    UpdateBounds(triangle);
}

void BoundingBox::CalculateBounds() {
    minPoint = vec3(FLT_MAX);
    maxPoint = vec3(-FLT_MAX);

    for (const auto& triangle : triangles) {
        UpdateBounds(triangle);
    }
}

void BoundingBox::UpdateBounds(const Triangle& triangle) {
    const vec3 vertices[] = { triangle.GetVertex0(), triangle.GetVertex1(), triangle.GetVertex2() };

    for (const auto& vertex : vertices) {
        minPoint.x = std::min(minPoint.x, vertex.x);
        minPoint.y = std::min(minPoint.y, vertex.y);
        minPoint.z = std::min(minPoint.z, vertex.z);

        maxPoint.x = std::max(maxPoint.x, vertex.x);
        maxPoint.y = std::max(maxPoint.y, vertex.y);
        maxPoint.z = std::max(maxPoint.z, vertex.z);
    }
}

void BoundingBox::Draw() const {
    glLineWidth(1.0f);
    glColor4f(color.r, color.g, color.b, color.a);
    GLfloat vertices[] = {
    minPoint.x, minPoint.y, minPoint.z,  // Vertex 1
    maxPoint.x, minPoint.y, minPoint.z,  // Vertex 2
    maxPoint.x, maxPoint.y, minPoint.z,  // Vertex 3
    minPoint.x, maxPoint.y, minPoint.z,  // Vertex 4
    minPoint.x, minPoint.y, maxPoint.z,  // Vertex 5
    maxPoint.x, minPoint.y, maxPoint.z,  // Vertex 6
    maxPoint.x, maxPoint.y, maxPoint.z,  // Vertex 7
    minPoint.x, maxPoint.y, maxPoint.z   // Vertex 8
    };

    GLushort indices[] = {
        0, 1, 1, 2, 2, 3, 3, 0,  // Bottom rectangle
        4, 5, 5, 6, 6, 7, 7, 4,  // Top rectangle
        0, 4, 1, 5, 2, 6, 3, 7   // Connecting lines
    };

    // Setup OpenGL state for drawing lines
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);

    // Setup vertex data
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    // Draw the wireframe box
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, indices);

    // Restore OpenGL state
    glDisableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

const vec3& BoundingBox::GetMin() const {
    return minPoint;
}

const vec3& BoundingBox::GetMax() const {
    return maxPoint;
}

const std::vector<Triangle>& BoundingBox::GetTriangles() const {
    return triangles;
}

bool BoundingBox::Intersects(const Ray& ray) const {
    float tmin = (minPoint.x - ray.GetOrigin().x) / ray.GetDirection().x;
    float tmax = (maxPoint.x - ray.GetOrigin().x) / ray.GetDirection().x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (minPoint.y - ray.GetOrigin().y) / ray.GetDirection().y;
    float tymax = (maxPoint.y - ray.GetOrigin().y) / ray.GetDirection().y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (minPoint.z - ray.GetOrigin().z) / ray.GetDirection().z;
    float tzmax = (maxPoint.z - ray.GetOrigin().z) / ray.GetDirection().z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    return true;
}
