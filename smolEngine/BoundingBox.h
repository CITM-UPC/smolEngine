#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "glmath.h"
#include "Triangle.h"
#include "Ray.h"
#include "Color.h"
#include <GL/glew.h>
#include <vector>

class BoundingBox {
public:
    BoundingBox();

    void AddTriangle(const Triangle& triangle);
    void CalculateBounds(bool rot); // Call this after adding all triangles

    const vec3& GetMin() const;
    const vec3& GetMax() const;
    const std::vector<Triangle>& GetTriangles() const;
    
    bool Intersects(const Ray& ray) const;
    void Draw() const;

    void SetTriangleVector(std::vector<Triangle> triangles) {
        this->triangles = triangles;
    }

    void SetBoundingBoxColor(const Color& color) {
        this->color = color;
    }

    std::vector<Triangle> triangles;

private:
    vec3 minPoint;
    vec3 maxPoint;
    
    Color color = White;

    glm::mat4 CreateRotationMatrix(float angleDegrees, const glm::vec3& axis);

    void UpdateBounds(const Triangle& triangle, bool rot = false);
    
};

#endif // BOUNDINGBOX_H
