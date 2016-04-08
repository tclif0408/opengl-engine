#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

#include <Project42\SpriteBatch.h>

#include "CollisionModel.h"

class PhysicsObject
{
public:
	PhysicsObject(glm::vec4 drawRect, GLuint texID, glm::vec2 vel = glm::vec2(0.0f));
	~PhysicsObject();
	void update();
	void draw(Proj42::SpriteBatch &sb);
	AABB getAABB();

private:
	glm::vec4 _drawingRect;
	glm::vec2 _velocity;
	GLuint _texID;
};

