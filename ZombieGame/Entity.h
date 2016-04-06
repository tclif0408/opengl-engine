#pragma once

#include "Drawable.h"

#include <Project42\ResourceManager.h>

class Entity: public Drawable
{
public:
	Entity(glm::vec4 boundingBox, GLuint textureID, glm::vec4 uv = GLOBAL_UV(), float depth = GLOBAL_DEPTH(), Proj42::Color color = WHITE())
		: Drawable(boundingBox, textureID, uv, depth, color) {}
	~Entity() {}

	virtual void update() { }

	float getRadius()
	{
		return _boundingBox.w / 2;
	}

	void setPosition(glm::vec2 newPos)
	{
		_boundingBox.x = newPos.x;
		_boundingBox.y = newPos.y;
	}

	glm::vec2 getCenterPosition()
	{
		return glm::vec2(_boundingBox[0] + _boundingBox[2] / 2.0f, _boundingBox[1] / _boundingBox[3] / 2.0f);
	}

	glm::vec2 getPosition()
	{
		return glm::vec2(_boundingBox.x, _boundingBox.y);
	}

protected:
	glm::vec2 _prevPosition;
};

