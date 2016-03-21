#pragma once

#include "Entity.h"

static GLuint ZombieTexture()
{
	return Proj42::ResourceManager::getTexture("Textures/circle.png").id;
}

static Proj42::Color ZombieColor()
{
	Proj42::Color zombieColor;
	zombieColor.r = 255;
	zombieColor.g = 255;
	zombieColor.b = 255;
	zombieColor.a = 255;
}

class Zombie: public Entity
{
public:
	Zombie(glm::vec4 boundingBox, glm::vec4 uv = GLOBAL_UV(), float depth = GLOBAL_DEPTH())
		: Entity(boundingBox, ZombieTexture(), uv, depth, ZombieColor()) {}
	~Zombie() {}

	void update();
};

