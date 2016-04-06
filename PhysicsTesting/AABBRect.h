#pragma once

#include <glm/glm.hpp>

class AABBRect {
public:
	AABBRect();
	AABBRect(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity);
	~AABBRect();

	glm::vec2 getMin();
	glm::vec2 getMax();
	glm::vec4 getPosAndSize();
	void update();

private:
	glm::vec2 _pos;
	glm::vec2 _size;
	glm::vec2 _velocity;

};
