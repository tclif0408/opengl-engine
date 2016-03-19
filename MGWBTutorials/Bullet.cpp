#include "Bullet.h"

#include <Project42\ResourceManager.h>

Bullet::Bullet(glm::vec2 pos, glm::vec2 direction, float speed, int ttl) :
	_position(pos),
	_direction(direction),
	_speed(speed),
	_ttl(ttl)
{
}

Bullet::~Bullet()
{
}

void Bullet::draw(Proj42::SpriteBatch & _spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Proj42::GLTexture texture = Proj42::ResourceManager::getTexture("Textures/pumpkin.png");
	Proj42::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize(_position.x, _position.y, 30.0f, 30.0f);

	_spriteBatch.draw(posAndSize, uv, color, 0.0f, texture.id);
}

bool Bullet::update()
{
	_position += _direction * _speed;
	return _ttl-- == 0;
}
