#pragma once

#include <glm/glm.hpp>

#include <cmath>

bool circleCollision(float r1, glm::vec2 pos1, float r2, glm::vec2 pos2)
{
	int dx = std::abs(pos1.x - pos2.x);
	int dy = std::abs(pos1.y - pos2.y);
	int dist = std::sqrt(dx * dx + dy * dy);
	return dist < r1 + r2;
}

/*
var rect1 = {x: 5, y: 5, width: 50, height: 50}
var rect2 = {x: 20, y: 10, width: 10, height: 10}

if (rect1.x < rect2.x + rect2.width &&
rect1.x + rect1.width > rect2.x &&
rect1.y < rect2.y + rect2.height &&
rect1.height + rect1.y > rect2.y) {
// collision detected!
}

// filling in the values =>

if (5 < 30 &&
55 > 20 &&
5 < 20 &&
55 > 10) {
// collision detected!
}
*/