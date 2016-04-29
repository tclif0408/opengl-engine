#pragma once

#include <Project42\DrawableGameComponent.h>
#include <Project42\InputManager.h>

class Player : public Proj42::DrawableGameComponent
{
public:
	Player(Proj42::InputManager* input, Proj42::Vector2 velocity, Proj42::Vector4 boundingBox, GLuint textureID, Proj42::Color color = Proj42::Color(255, 255, 255, 255), float depth = 0.0f)
		: Proj42::DrawableGameComponent(boundingBox, textureID, color, depth)
	{
		_velocity = Proj42::Vector2(0.0f);
		_input = input;
	}
	~Player() {}

	void update();

private:
	Proj42::Vector2 _velocity;
	Proj42::InputManager* _input;
};

