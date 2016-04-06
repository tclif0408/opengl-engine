#pragma once

#include "Entity.h"
#include "Drawable.h"

#include <glm/glm.hpp>

#include <cmath>
#include <math.h>

bool circleCollision(float r1, glm::vec2 pos1, float r2, glm::vec2 pos2)
{
	int dx = std::abs(pos1.x - pos2.x);
	int dy = std::abs(pos1.y - pos2.y);
	int dist = std::sqrt(dx * dx + dy * dy);
	return dist < r1 + r2;
}

bool circleRectCollision(glm::vec2 circlePos, float radius, glm::vec4 rect)
{
	glm::vec2 circleDist = glm::vec2(std::abs(circlePos.x - rect.x), std::abs(circlePos.y - rect.y));

	if (circleDist.x > (rect[2] / 2 + radius))
		return false;
	if (circleDist.y > (rect[3] / 2 + radius))
		return false;

	if (circleDist.x <= (rect[2] / 2))
		return true;
	if (circleDist.y <= (rect[3] / 2)) 
		return true;

	float cornerDistance_sq = std::pow(circleDist.x - rect[2] / 2, 2) + std::pow(circleDist.y - rect[3] / 2, 2);

	return (cornerDistance_sq <= (radius * radius));
}

// push one moving thing out of another
void resolveCollision()
{
	return;
}

bool rectCollision(glm::vec4& r1, glm::vec4 r2)
{
	if (r1.x < r2.x + r2[2] &&
		r1.x + r1[2] > r2.x &&
		r1.y < r2.y + r2[3] &&
		r1[3] + r1.y > r2.y)
		return true;
}