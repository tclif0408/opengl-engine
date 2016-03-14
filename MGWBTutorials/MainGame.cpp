#include <iostream>
#include <string>

#include "MainGame.h"

#include <Project42\Proj42.h>
#include <Project42\Errors.h>
#include <Project42\Proj42.h>

MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_gameState(GameState::PLAY),
	_time(0.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();

	// push back some sprites
	_sprites.push_back(new Proj42::Sprite());
	_sprites.back()->init(0.0f, 0.0f, _screenWidth / 2, _screenWidth / 2, "Textures/roxy.png");

	_sprites.push_back(new Proj42::Sprite());
	_sprites.back()->init(_screenWidth / 2, 0.0f, _screenWidth / 2, _screenWidth / 2, "Textures/roxy.png");

	gameLoop();
}

void MainGame::initSystems()
{
	Proj42::init();
	_window.create("Game Engine", _screenWidth, _screenHeight, 0);
	initShaders();										// initialize shaders
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
			switch (sdlEvent.key.keysym.sym) {
				// move camera based on input
			case SDLK_w:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAM_SPEED));
				break;
			case SDLK_s:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAM_SPEED));
				break;
			case SDLK_a:
				_camera.setPosition(_camera.getPosition() + glm::vec2(CAM_SPEED, 0.0f));
				break;
			case SDLK_d:
				_camera.setPosition(_camera.getPosition() + glm::vec2(-CAM_SPEED, 0.0f));
				break;
			case SDLK_q:
				_camera.setScale(_camera.getScale() + SCALE_SPEED);
				break;
			case SDLK_e:
				_camera.setScale(_camera.getScale() + -SCALE_SPEED);
				break;
			}
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
	for (int i = 0; i < _sprites.size(); i++)
		_sprites[i]->draw();

	glBindTexture(GL_TEXTURE_2D, 0);						// unbind the texture
	_colorProgram.unuse();									// unuse program
	_window.swapBuffer();									// swap buffer
}

void MainGame::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static float prevTicks = SDL_GetTicks();
	static int currentFrame = 0;

	float currentTicks;
	float frameTimeAverage = 0;
	int count;

	currentTicks = SDL_GetTicks();
	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
	prevTicks = currentTicks;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	for (int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
		_fps = 1000.0f / frameTimeAverage;
	else
		_fps = 60.0f;		// just fake it
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		static int frameCounter = 0;

		float startTicks = SDL_GetTicks();		// for frame time measuring
		float frameTicks;
		float desiredFPS;

		processInput();
		_time += 0.01f;		// update time uniform variable
		_camera.update();	// update camera
		drawGame();
		calculateFPS();

		// print once every 100 frames
		if (frameCounter++ == 100)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		// limit fps to the max fps
		frameTicks = SDL_GetTicks() - startTicks;
		desiredFPS = 1000.0f / MAX_FPS;

		if (desiredFPS > frameTicks)
			SDL_Delay(desiredFPS - frameTicks);
	}
}
