#include "Triangle.h"

Triangle::Triangle(const vec3& v0, const vec3& v1, const vec3& v2)
    : vertex0(v0), vertex1(v1), vertex2(v2) {}

const vec3& Triangle::GetVertex0() const {
    return vertex0;
}

const vec3& Triangle::GetVertex1() const {
    return vertex1;
}

const vec3& Triangle::GetVertex2() const {
    return vertex2;
}
