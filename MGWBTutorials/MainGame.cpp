#include <iostream>
#include <string>

#include "MainGame.h"

#include <Project42\Proj42.h>
#include <Project42\Errors.h>

MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_gameState(GameState::PLAY),
	_time(0.0f),
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
	const float CAM_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;

	SDL_Event sdlEvent;
	
	while (SDL_PollEvent(&sdlEvent))
		switch (sdlEvent.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << sdlEvent.motion.x << " " << sdlEvent.motion.y << "\n";
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(sdlEvent.key.keysym.sym);
			break;
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

	// send uniform time variable to the glsl program
	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	// send camera matrix to the glsl program
	GLint projectionLocation = _colorProgram.getUniformLocation("projection");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	// actually draw stuff!
	_spriteBatch.begin();

	glm::vec4 position(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	float depth = 0;
	static GLuint texture = Proj42::ResourceManager::getTexture("Textures/vriska.png").id;
	Proj42::Color color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.draw(position, uv, color, depth, texture);

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

		//float startTicks = SDL_GetTicks();		// for frame time measuring
		//float frameTicks;
		//float desiredFPS;

		_fpsLimiter.begin();

		processInput();
		_time += 0.01f;		// update time uniform variable
		_camera.update();	// update camera
		drawGame();

		_framerate = _fpsLimiter.end();

		// print once every 100 frames
		if (frameCounter++ == 100)
		{
			std::cout << _framerate << std::endl;
			frameCounter = 0;
		}

		// limit fps to the max fps
		//frameTicks = SDL_GetTicks() - startTicks;
		//desiredFPS = 1000.0f / MAX_FPS;
		//
		//if (desiredFPS > frameTicks)
		//	SDL_Delay(desiredFPS - frameTicks);
	}
}
