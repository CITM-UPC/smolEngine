#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "glmath.h"

class Triangle {
public:
    Triangle(const vec3& v0, const vec3& v1, const vec3& v2);

    const vec3& GetVertex0() const;
    const vec3& GetVertex1() const;
    const vec3& GetVertex2() const;

private:
    vec3 vertex0;
    vec3 vertex1;
    vec3 vertex2;
};

#endif // TRIANGLE_H
