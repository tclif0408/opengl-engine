#include "PhysicsTest.h"

#include "Physics.h"

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

#include <Project42\Proj42.h>
#include <Project42\Errors.h>
#include <Project42\ResourceManager.h>

PhysicsTest::PhysicsTest() :
	_screenWidth(1024),
	_screenHeight(768),
	_state(State::PLAY),
	_maxFPS(60.0f)
{
	_rects.emplace_back(glm::vec2(0.0f, 0.0f), glm::vec2(30.0f, 30.0f), glm::vec2(1.0f, 1.0f));
	_rects.emplace_back(glm::vec2((float)_screenWidth - 30.0f, (float)_screenHeight - 30.0f), glm::vec2(30.0f, 30.0f), glm::vec2(-1.0f, -1.0f));

	_rects.emplace_back(glm::vec2(0.0f, 300.0f), glm::vec2(30.0f, 30.0f), glm::vec2(1.0f, 0.0f));
	_rects.emplace_back(glm::vec2(900.0f, 300.0f), glm::vec2(30.0f, 30.0f), glm::vec2(-1.0f, 0.0f));

	_camera.init(_screenWidth, _screenHeight);
	_camera.setPosition(_camera.getPosition() + glm::vec2(_screenWidth / 2, _screenHeight / 2));
}

PhysicsTest::~PhysicsTest()
{
}

void PhysicsTest::run()
{
	initSystems();
	gameLoop();
}

void PhysicsTest::initSystems()
{
	Proj42::init();
	_window.create("Physics test", _screenWidth, _screenHeight, 0);
	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void PhysicsTest::initShaders()
{
	_shaderProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_shaderProgram.addAttribute("vertexPosition");
	_shaderProgram.addAttribute("vertexColor");
	_shaderProgram.addAttribute("vertexUV");
	_shaderProgram.linkShaders();
}

void PhysicsTest::processInput()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			_state = State::EXIT;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(sdlEvent.key.keysym.sym);
			break;
		}
}

void PhysicsTest::update()
{
	if (_inputManager.isKeyPressed(SDLK_ESCAPE))
		_state = State::EXIT;

	for (unsigned int i = 0; i < _rects.size(); i++)
		_rects[i].update();

	static int collideCount = 0;

	// test for collisions
	for (unsigned int i = 0; i < _rects.size(); i++)
		for (unsigned int j = 0; j < _rects.size(); j++)
			if (i == j)
				continue;
			else
				if (AABBvsAABB(_rects[i], _rects[j]))
				{
					std::printf("There was a collision! %d\n", collideCount++);
				}
}

void PhysicsTest::drawGame()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shaderProgram.use();
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = _shaderProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	GLint projectionLocation = _shaderProgram.getUniformLocation("projection");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	_spriteBatch.begin();

	for (unsigned int i = 0; i < _rects.size(); i++)
	{
		static GLuint textureID = Proj42::ResourceManager::getTexture("Textures/block.png").id;
		Proj42::Color white;
		white.r = 255;
		white.g = 255;
		white.b = 255;
		white.a = 255;

		_spriteBatch.draw(_rects[i].getPosAndSize(), glm::vec4(0.0, 0.0, 1.0f, 1.0f), white, 0, textureID);

	}
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_shaderProgram.unuse();
	_window.swapBuffer();
}

void PhysicsTest::gameLoop()
{
	while (_state != State::EXIT)
	{
		static int frameCounter = 0;
		_fpsLimiter.begin();
		processInput();
		_camera.update();

		update();
		drawGame();

		_framerate = _fpsLimiter.end();

		// print once every 1000 frames
		if (frameCounter++ == 1000)
		{
			std::cout << _framerate << "\n";
			frameCounter = 0;
		}
	}
}
