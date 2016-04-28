#include "PhysicsTest.h"

void PhysicsTest::initialize()
{
	Game::setCameraPos(Game::CenterScreen());

	

	_physicsObjects.emplace_back(glm::vec2(1.0f, 2.0f), this, glm::vec4(0.0f, 0.0f, 30.0f, 30.0f), Game::getTextureID("Textures/block.png"));
	_physicsObjects.emplace_back(glm::vec2(2.0f, 1.0f), this, glm::vec4(50.0f, 50.0f, 30.0f, 30.0f), Game::getTextureID("Textures/block.png"));
	_physicsObjects.emplace_back(glm::vec2(-1.0f, 2.0f), this, glm::vec4(100.0f, 200.0f, 30.0f, 30.0f), Game::getTextureID("Textures/block.png"));

}

void PhysicsTest::update()
{
	if (Game::isKeyPressed(SDLK_ESCAPE))
		_gameState = Proj42::GameState::EXIT;

	Game::update();
}

void PhysicsTest::draw()
{
	Game::update();
}
