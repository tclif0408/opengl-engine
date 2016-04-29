#include "PhysicsTest.h"

#include <Project42\Keys.h>

using namespace Proj42;

void PhysicsTest::initialize()
{
	Game::setCameraPos(Game::CenterScreen());

	_physicsObjects.emplace_back(Vector2(0.0f, 2.0f), Vector4(529.0f, 0.0f, 30.0f, 30.0f), Game::getTextureID("Textures/block.png"));
	_physicsObjects.emplace_back(Vector2(0.0f, -2.0f), Vector4(500.0f, 500.0f, 30.0f, 30.0f), Game::getTextureID("Textures/block.png"));

	for (unsigned int i = 0; i < _physicsObjects.size(); i++)
		Game::addGameComponent(&_physicsObjects[i]);
}

void PhysicsTest::update()
{
	if (Game::isKeyPressed(Keys::ESCAPE))
		_gameState = GameState::EXIT;

	Game::update();

	for (unsigned int i = 0; i < _physicsObjects.size(); i++)
		for (unsigned int j = 0; j < _physicsObjects.size(); j++)
			if (i == j)
				continue;
			else if (rectsIntersect(_physicsObjects[i].getBoundingBox(), _physicsObjects[j].getBoundingBox()))
			{
				printf("There was a collision\n");
				resolveCollision(&_physicsObjects[i].getBoundingBox(), &_physicsObjects[j].getBoundingBox());
			}
}
