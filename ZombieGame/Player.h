#pragma once

#include "Entity.h"

class Game;

#include <Project42\vertex.h>
#include <Project42\ResourceManager.h>

static Proj42::Color PlayerColor()
{
	Proj42::Color playerColor;
	playerColor.r = 255;
	playerColor.r = 0;
	playerColor.r = 128;
	playerColor.r = 255;
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
	Player(glm::vec4 boundingBox, Game* game, glm::vec4 uv = GLOBAL_UV(), float depth = GLOBAL_DEPTH());
	~Player();

	void update();

	glm::vec2 getPosition() { return glm::vec2(_boundingBox.x, _boundingBox.y); }

private:
	Game* _game;
};

