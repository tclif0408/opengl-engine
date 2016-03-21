#pragma once

#include "Entity.h"

class Game;

#include <Project42\vertex.h>

static Proj42::Color PlayerColor()
{
	Proj42::Color playerColor;
	playerColor.r = 255;
	playerColor.g = 0;
	playerColor.b = 128;
	playerColor.a = 255;
	return playerColor;
}

static GLuint PlayerTexture()
{
	return Proj42::ResourceManager::getTexture("Textures/circle.png").id;
}

const float PLAYER_SPEED = 5.0f;


class Player: public Entity
{
public:
	Player::Player(glm::vec4 boundingBox, Game* game, glm::vec4 uv = GLOBAL_UV(), float depth = GLOBAL_DEPTH())
		: Entity(boundingBox, PlayerTexture(), uv, depth, PlayerColor())
	{
		_game = game;
	}
	~Player() {}

	void update();

private:
	Game* _game;
};

