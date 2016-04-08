#include "PhysicsObject.h"

#include <Project42\Errors.h>

PhysicsObject::PhysicsObject(glm::vec4 drawRect, GLuint texID, glm::vec2 vel) :
	_drawingRect(drawRect), _texID(texID), _velocity(vel)
{
}

PhysicsObject::~PhysicsObject()
{
}

AABB PhysicsObject::getAABB()
{
	return AABB(glm::vec2(_drawingRect.x, _drawingRect.y), glm::vec2(_drawingRect.x + _drawingRect.z, _drawingRect.y + _drawingRect.z));
}

void PhysicsObject::update()
{
	_drawingRect.x = _drawingRect.x + _velocity.x;
	_drawingRect.y = _drawingRect.y + _velocity.y;
}

void PhysicsObject::draw(Proj42::SpriteBatch &sb)
{
	static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static float depth = 0;
	Proj42::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	sb.draw(_drawingRect, uv, color, depth, _texID);
}