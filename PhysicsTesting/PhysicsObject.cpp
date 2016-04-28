#include "PhysicsObject.h"

<<<<<<< Updated upstream
// glm::vec4 --> x y z w
=======
using namespace Proj42;
>>>>>>> Stashed changes

void PhysicsObject::update()
{
	DrawableGameComponent::setPosition(DrawableGameComponent::getPosition() + _velocity);
}
