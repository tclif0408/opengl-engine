#include "Player.h"
#include "Game.h"

Player::Player(glm::vec4 boundingBox, Game* game, glm::vec4 uv, float depth)
	: Entity(boundingBox, PlayerTexture(), uv, depth, PlayerColor())
{
	_game = game;
}

Player::~Player()
{
}

void Player::update()
{
	// update based on input
	if (_game->InputManager.isKeyPressed(SDLK_w))
		_boundingBox.y += PLAYER_SPEED;
	if (_game->InputManager.isKeyPressed(SDLK_s))
		_boundingBox.y -= PLAYER_SPEED;
	if (_game->InputManager.isKeyPressed(SDLK_a))
		_boundingBox.x -= PLAYER_SPEED;
	if (_game->InputManager.isKeyPressed(SDLK_d))
		_boundingBox.x += PLAYER_SPEED;
}
