#ifndef RAY_H
#define RAY_H


#include "glmath.h"
#include "types.h"

class Ray {
public:

    Ray(const vec3& origin, const vec3& direction);

    vec3 PointAtParameter(float t) const;

    const vec3& GetOrigin() const;
    const vec3& GetDirection() const;

private:
    vec3 origin;
    vec3 direction;
};

#endif // RAY_H

