#pragma once

/*
	http://www.metanetsoftware.com/technique/tutorialA.html
	https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects
	https://www.reddit.com/r/gamedev/comments/15kk3w/can_you_recommend_a_simple_open_source_2d_game/
	http://www.gamedev.net/topic/593498-hopefully-simple-collision-resolution-question/

	http://hamaluik.com/haxe-glm/glm/Vec4.html

	https://en.wikipedia.org/wiki/Teeworlds
	https://en.wikipedia.org/wiki/Secret_Maryo_Chronicles

	x, y, z, w <-- glm::vec4
*/

#include "CollisionModel.h"


bool collideAABBs(AABB* a, AABB* b)
{
	float d1x = b->min.x - a->max.x;
	float d1y = b->min.y - a->max.y;
	float d2x = a->min.x - b->max.x;
	float d2y = a->min.y - b->max.y;

	if (d1x > 0.0f || d1y > 0.0f)
		return false;

	if (d2x > 0.0f || d2y > 0.0f)
		return false;

	return true;
}

bool collideCircles(Circle *a, Circle* b)
{
	float x = a->pos.x - b->pos.x;
	float y = a->pos.y - b->pos.y;
	float centerDistanceSq = x * x + y * y;
	float radius = a->r + b->r;
	float radiusSq = radius * radius;
	return centerDistanceSq <= radiusSq;
}
