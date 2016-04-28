#pragma once

#include "Physics.h"
#include "PhysicsTest.h"
#include <Project42\DrawableGameComponent.h>

class PhysicsObject : public Proj42::DrawableGameComponent {

public:
	PhysicsObject(glm::vec2 velocity, PhysicsTest* game, glm::vec4 boundingBox, GLuint textureID, Proj42::Color color = Proj42::Color(255, 255, 255, 255), float depth = 0.0f)
		: DrawableGameComponent(game, boundingBox, textureID, color, depth)
	{
		_velocity = velocity;
	}
	~PhysicsObject() { }

	void update();
	AABB getAABB();

private:

	glm::vec2 _velocity;

};
