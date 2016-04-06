#pragma once

#include "AABBRect.h"

bool AABBvsAABB(AABBRect a, AABBRect b)
{
	glm::vec2 amax = a.getMax();
	glm::vec2 amin = a.getMin();
	glm::vec2 bmax = b.getMax();
	glm::vec2 bmin = b.getMin();

	// if found separated along an axis, there is no intersection.
	if (amax.x < bmin.x || amin.x > bmax.x) return false;
	if (amax.y < bmin.y || amin.y > bmin.y) return false;
	// no separating axis found, so there must be an overlap.
	return true;
}