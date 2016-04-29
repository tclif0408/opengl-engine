#include "ZombieGame.h"

using namespace Proj42;

void ZombieGame::initialize()
{
	Game::setCameraPos(Game::CenterScreen());

	_player = new Player(&_inputManager, Vector2(0.0f), Vector4(0.0f, 0.0f, 50.0f, 50.0f), Proj42::ResourceManager::getTexture("Textures/roxy.png").id);

	Game::addGameComponent(_player);
}

void ZombieGame::update()
{
	if (_inputManager.isKeyPressed(Keys::ESCAPE))
		Game::setGameState(GameState::EXIT);

	Game::update();

	// TODO: Implement game update logic.
}
