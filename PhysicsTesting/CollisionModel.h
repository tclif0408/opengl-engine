#pragma once

struct AABB {
	glm::vec2 min;
	glm::vec2 max;

	AABB(glm::vec2 mi, glm::vec2 ma)
		: min(mi), max(ma) {}
};

struct Circle {
	glm::vec2 pos;
	float r;

	Circle(glm::vec2 position, float radius)
		: pos(position), r(radius) {}
};