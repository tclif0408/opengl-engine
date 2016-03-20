#pragma once

#include "Entity.h"

#include <Project42\ResourceManager.h>

static GLuint CivillianTexture()
{
	return Proj42::ResourceManager::getTexture("Textures/circle.png").id;
}

static Proj42::Color CivillianColor()
{
	Proj42::Color color;
	color.r = 161;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	return color;
}

class Civillian: public Entity
{
public:
	Civillian(glm::vec4 boundingBox, float depth = GLOBAL_DEPTH(), glm::vec4 uv = GLOBAL_UV())
		: Entity(boundingBox, CivillianTexture(), uv, depth, CivillianColor()) {}
	~Civillian() {}

	void update() override;
};

