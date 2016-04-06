#include "AABBRect.h"

AABBRect::AABBRect()
{
}

AABBRect::AABBRect(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity)
	: _pos(pos), _size(size), _velocity(velocity)
{
}

AABBRect::~AABBRect()
{
}

glm::vec2 AABBRect::getMin() { return glm::vec2(_pos); }
glm::vec2 AABBRect::getMax() { return glm::vec2(_pos + _size); }
glm::vec4 AABBRect::getPosAndSize() { return glm::vec4(_pos, _size); }

void AABBRect::update()
{
	_pos += _velocity;
}
