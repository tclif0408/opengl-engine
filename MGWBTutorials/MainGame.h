#pragma once

#include <SDL/sdl.h>
#include <GL/glew.h>

#include <vector>

#include <Project42/Sprite.h>
#include <Project42/GLSLProgram.h>
#include <Project42/GLTexture.h>
#include <Project42/Window.h>
#include <Project42/Camera2D.h>
#include <Project42/SpriteBatch.h>
#include <Project42/InputManager.h>
#include <Project42/Timing.h>

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();					// run game
	void initSystems();			// initialize systems
	void initShaders();
	void processInput();
	void drawGame();
	void calculateFPS();

private:
	void gameLoop();

	Proj42::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	Proj42::GLSLProgram _colorProgram;
	float _time;
	float _maxFPS;
	float _framerate;
	Proj42::Camera2D _camera;
	Proj42::SpriteBatch _spriteBatch;
	Proj42::InputManager _inputManager;
	Proj42::FPSLimiter _fpsLimiter;
};

