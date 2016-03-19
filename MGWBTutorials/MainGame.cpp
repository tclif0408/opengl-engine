#include <iostream>
#include <string>

#include "MainGame.h"

#include <Project42\Proj42.h>
#include <Project42\Errors.h>

MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	gameLoop();
}

void MainGame::initSystems()
{
	Proj42::init();
	_window.create("Game Engine", _screenWidth, _screenHeight, 0);
	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::processInput()
{
	const float CAM_SPEED = 2.0f;
	const float SCALE_SPEED = 0.05f;

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

	if (_inputManager.isKeyPressed(SDLK_w))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAM_SPEED));
	if (_inputManager.isKeyPressed(SDLK_s))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAM_SPEED));
	if (_inputManager.isKeyPressed(SDLK_a))
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAM_SPEED, 0.0f));
	if (_inputManager.isKeyPressed(SDLK_d))
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAM_SPEED, 0.0f));
	if (_inputManager.isKeyPressed(SDLK_q))
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
		if (_camera.getScale() < 0.0f) _camera.setScale(0.0f);
	}

	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorldCoords(mouseCoords);

		glm::vec2 playerPos(0.0f);
		glm::vec2 direction = mouseCoords - playerPos;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPos, direction, 5.0f, 1000);
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffer
	
	_colorProgram.use();									// use program
	glActiveTexture(GL_TEXTURE0);							// use the first texture

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	// send camera matrix to the glsl program
	GLint projectionLocation = _colorProgram.getUniformLocation("projection");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	// actually draw stuff!
	_spriteBatch.begin();

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

	for (int i = 0; i < _bullets.size(); i++)
		_bullets[i].draw(_spriteBatch);

	// end of drawing code
	_spriteBatch.end();

	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);						// unbind the texture
	_colorProgram.unuse();									// unuse program
	_window.swapBuffer();									// swap buffer
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		static int frameCounter = 0;

		_fpsLimiter.begin();

		processInput();
		_camera.update();	// update camera

		// update bullets
		for (int i = 0; i < _bullets.size(); )
			if (_bullets[i].update())
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else i++;

		drawGame();

		_framerate = _fpsLimiter.end();

		// print once every 100 frames
		if (frameCounter++ == 10000)
		{
			std::cout << _framerate << std::endl;
			frameCounter = 0;
		}
	}
}
