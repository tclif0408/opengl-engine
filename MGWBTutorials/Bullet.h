#pragma once

#include <glm/glm.hpp>

#include <Project42/SpriteBatch.h>

class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 direction, float speed, int ttl);
	~Bullet();

	void draw(Proj42::SpriteBatch& _spriteBatch);
	bool update();		// returns true at end of the bullet's lifetime

private:
	float _speed;
	int _ttl;
	glm::vec2 _direction;
	glm::vec2 _position;
};

