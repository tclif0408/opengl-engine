#pragma once

#include "Drawable.h"

class Entity: public Drawable
{
public:
	Entity(glm::vec4 boundingBox, GLuint textureID, glm::vec4 uv = GLOBAL_UV(), float depth = GLOBAL_DEPTH(), Proj42::Color color = WHITE())
		: Drawable(boundingBox, textureID, uv, depth, color) {}
	~Entity() {}

	virtual void update() {};

	float getRadius()
	{
		return _boundingBox.w / 2;
	}

	glm::vec2 getPosition()
	{
		return glm::vec2(_boundingBox.x, _boundingBox.y);
	}
};

