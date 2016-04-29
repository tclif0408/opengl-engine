#include "Game.h"

namespace Proj42 {

	Game::Game(
		int windowWidth,
		int windowHeight,
		ShaderInfo* shaderInfo)
	{
		_gameState = GameState::PLAY;
		_screenWidth = windowWidth;
		_screenHeight = windowHeight;
		_maxFPS = 30.0f;
		_shaderInfo = shaderInfo;

		_camera.init(_screenWidth, _screenHeight);
	}

	Game::~Game()
	{
	}

	void Game::run()
	{
		initSystems();
		initialize();
		gameLoop();
	}

	void Game::initSystems()
	{
		Proj42::init();
		_window.create(_windowTitle, _screenWidth, _screenHeight, _windowFlags);
		initShaders();
		_spriteBatch.init();
		_fpsLimiter.init(_maxFPS);
	}

	void Game::update()
	{
		for (unsigned int i = 0; i < _components.size(); i++)
			_components[i]->update();
	}

	void Game::draw()
	{
		for (unsigned int i = 0; i < _components.size(); i++)
			if (DrawableGameComponent* drawable = dynamic_cast<DrawableGameComponent*>(_components[i]))
				drawable->draw(_spriteBatch);
	}

	void Game::gameLoop()
	{
		while (_gameState != GameState::EXIT)
		{
			_fpsLimiter.begin();
			processInput();
			_camera.update();

			update();

			setUpDraw();
			draw();
			endDraw();

			_currentFramerate = _fpsLimiter.end();
		}
	}

	void Game::initShaders()
	{
		_shaderProgram.compileShaders(_shaderInfo->vertexPath, _shaderInfo->fragmentPath);

		for (unsigned int i = 0; i < _shaderInfo->attributes.size(); i++)
			_shaderProgram.addAttribute(_shaderInfo->attributes[i]);

		_shaderProgram.linkShaders();
	}

	void Game::processInput()
	{
		SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent))
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
				_inputManager.pressKey(sdlEvent.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.releaseKey(sdlEvent.key.keysym.sym);
				break;
			}
	}

	void Game::setUpDraw()
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
	}

	void Game::endDraw()
	{
		_spriteBatch.end();
		_spriteBatch.renderBatch();

		glBindTexture(GL_TEXTURE_2D, 0);
		_shaderProgram.unuse();
		_window.swapBuffer();
	}
};