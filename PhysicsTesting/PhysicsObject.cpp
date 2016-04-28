#include "PhysicsObject.h"

void PhysicsObject::update()
{
	DrawableGameComponent::setPosition(DrawableGameComponent::getPosition() + _velocity);
}
