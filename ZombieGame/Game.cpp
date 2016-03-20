#include "Game.h"

#include "Collisions.h"

#include <iostream>

#include <Project42\Proj42.h>

Game::Game() :
	_screenWidth(1024),
	_screenHeight(786),
	_gameState(GameState::PLAY),
	_desiredFramerate(60.0f)	
{
	_camera.init(_screenWidth, _screenHeight);
	_camera.setScale(1.5f);
}

Game::~Game()
{
	delete _player;
}

void Game::run()
{
	initSystems();
	gameLoop();
}

void Game::initSystems()
{
	Proj42::init();
	_window.create("Zombie Game", _screenWidth, _screenHeight, 0);
	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(_desiredFramerate);
}

void Game::initShaders()
{
	_shaderProgram.compileShaders("Shaders/colors.vert", "Shaders/colors.frag");
	_shaderProgram.addAttribute("vertexPosition");
	_shaderProgram.addAttribute("vertexColor");
	_shaderProgram.addAttribute("vertexUV");
	_shaderProgram.linkShaders();
}

void Game::processInput()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
		switch (sdlEvent.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			InputManager.setMouseCoords(sdlEvent.motion.x, sdlEvent.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			InputManager.pressKey(sdlEvent.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			InputManager.releaseKey(sdlEvent.button.button);
			break;
		case SDL_KEYDOWN:
			InputManager.pressKey(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			InputManager.releaseKey(sdlEvent.key.keysym.sym);
			break;
		}
}

void Game::drawGame()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgram.use();
	glActiveTexture(GL_TEXTURE0);

	GLint projectionLocation = _shaderProgram.getUniformLocation("projection");
	glm::mat4 cameraMat = _camera.getCameraMatrix();
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &cameraMat[0][0]);

	_spriteBatch.begin();

	for (int i = 0; i < _testwalls.size(); i++)
		_testwalls[i].draw(_spriteBatch);

	for (int i = 0; i < _civies.size(); i++)
		_civies[i].draw(_spriteBatch);

	_player->draw(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_shaderProgram.unuse();
	_window.swapBuffer();
}

void Game::updateGame()
{
	// exit the game with the escape key
	if (InputManager.isKeyPressed(SDLK_ESCAPE))
		_gameState = GameState::EXIT;

	// update the player
	_player->update();

	// update civillians
	for (int i = 0; i < _civies.size(); i++)
		_civies[i].update();

	// have the camera track the player
	_camera.setPosition(_player->getPosition());

	// collide player with civillians
	for (int i = 0; i < _civies.size(); i++)
		if (circleCollision(_player->getRadius(), _player->getPosition(), _civies[i].getRadius(), _civies[i].getPosition()))
			std::cout << "Collision!\n";
		else
			std::cout << "No Collision!\n";

	_camera.update();
}

void Game::gameLoop()
{
	_testwalls.emplace_back(glm::vec4(0.0f, 0.0f, 30.0f, 30.0f), WallType::BRICK);
	_testwalls.emplace_back(glm::vec4(0.0f, 30.0f, 30.0f, 30.0f), WallType::BRICK);
	_testwalls.emplace_back(glm::vec4(40.0f, 0.0f, 30.0f, 30.0f), WallType::GLASS);
	_testwalls.emplace_back(glm::vec4(70.0f, 20.0f, 30.0f, 30.0f), WallType::GLASS);

	_civies.emplace_back(glm::vec4(100.0f, 100.0f, 30.0f, 30.0f));
	_civies.emplace_back(glm::vec4(140.0f, 140.0f, 30.0f, 30.0f));

	_player = new Player(glm::vec4(0.0f, 0.0f, 30.0f, 30.0f), this);

	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.begin();
		processInput();
		updateGame();
		drawGame();
		_currentFramerate = _fpsLimiter.end();
	}
}
