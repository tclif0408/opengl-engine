#include "PhysicsObject.h"

// glm::vec4 --> x y z w

void PhysicsObject::update()
{
	DrawableGameComponent::setPosition(DrawableGameComponent::getPosition() + _velocity);
}

AABB PhysicsObject::getAABB()
{
	glm::vec4 rect = DrawableGameComponent::getBoundingBox();
	return AABB(glm::vec2(rect.x, rect.y), glm::vec2(rect.x + rect.z, rect.y + rect.w));
}
