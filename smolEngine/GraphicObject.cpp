#include "GraphicObject.h"
#include <GL/glew.h>

GraphicObject::GraphicObject() : _transform(glm::identity<mat4>()) {}
GraphicObject::GraphicObject(std::shared_ptr<Mesh> graphic) : _transform(glm::identity<mat4>()), _graphic(graphic) {}

void GraphicObject::move(const dvec3& displacement)
{
	_transform = glm::translate(_transform, displacement);
	for (auto& child : children()) ((GraphicObject&)child).move(displacement);
}

void GraphicObject::rotate(double rads, const dvec3& axis)
{
	_transform = glm::rotate(_transform, rads, axis);
	for (auto& child : children()) ((GraphicObject&)child).rotate(rads, axis);
}

void GraphicObject::scale(const dvec3& s)
{
	_transform = glm::scale(_transform, s);
	for (auto& child : children()) ((GraphicObject&)child).scale(s);
}

void GraphicObject::setTransformation(mat4 m)
{
	_transform += m;
	for (auto& child : children()) ((GraphicObject&)child).setTransformation(m);
}

void GraphicObject::paint() const {
	glPushMatrix();
	glMultMatrixd(&_transform[0].x);
	if (_graphic.get()) _graphic->draw();
	for (auto& child : children()) ((GraphicObject&)child).paint();
	glPopMatrix();
}
