#pragma once

#include "Drawable.h"

enum class WallType { BRICK, GLASS };

class Wall: public Drawable
{
public:
	Wall(glm::vec4 boundingBox, WallType wallType, glm::vec4 uv = GLOBAL_UV(), float depth = GLOBAL_DEPTH(), Proj42::Color color = WHITE());
	~Wall();
};

