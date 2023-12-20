#include "Ray.h"

Ray::Ray(const vec3& origin, const vec3& direction) : origin(origin), direction(normalize(direction)) {  }

vec3 Ray::PointAtParameter(float t) const {
    return origin + t * direction;
}

const vec3& Ray::GetOrigin() const {
    return origin;
}

const vec3& Ray::GetDirection() const {
    return direction;
}
