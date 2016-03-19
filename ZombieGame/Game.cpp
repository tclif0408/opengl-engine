#include "Game.h"

#include <Project42\Proj42.h>

Game::Game() :
	_screenWidth(1024),
	_screenHeight(786),
	_gameState(GameState::PLAY),
	_desiredFramerate(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

Game::~Game()
{
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
			_inputManager.setMouseCoords(sdlEvent.motion.x, sdlEvent.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(sdlEvent.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(sdlEvent.button.button);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(sdlEvent.key.keysym.sym);
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

	/*	Example drawing code:

	glm::vec4 position(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	float depth = 0;
	static GLuint texture = Proj42::ResourceManager::getTexture("Textures/maryo.png").id;
	Proj42::Color color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.draw(position, uv, color, depth, texture);
	
	*/

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_shaderProgram.unuse();
	_window.swapBuffer();
}

void Game::updateGame()
{
	_camera.update();
}

void Game::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.begin();
		processInput();
		updateGame();
		drawGame();
		_currentFramerate = _fpsLimiter.end();
	}
}
