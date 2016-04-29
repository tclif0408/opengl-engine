#include "Player.h"

using namespace Proj42;

void Player::update()
{
	if (_input->isKeyPressed(Keys::W))
		DrawableGameComponent::setPosition(DrawableGameComponent::getPosition() + Vector2(0.0f, 10.0f));	// move up
	if (_input->isKeyPressed(Keys::S))
		DrawableGameComponent::setPosition(DrawableGameComponent::getPosition() + Vector2(0.0f, -10.0f));	// move down
	if (_input->isKeyPressed(Keys::A))
		DrawableGameComponent::setPosition(DrawableGameComponent::getPosition() + Vector2(-10.0f, 0.0f));	// move left
	if (_input->isKeyPressed(Keys::D))
		DrawableGameComponent::setPosition(DrawableGameComponent::getPosition() + Vector2(10.0f, 0.0f));	// move right
}
