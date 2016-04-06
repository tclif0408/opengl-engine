#pragma once

#include <Project42\Window.h>
#include <Project42\GLSLProgram.h>
#include <Project42\Camera2D.h>
#include <Project42\SpriteBatch.h>
#include <Project42\InputManager.h>
#include <Project42\Timing.h>

#include <vector>

#include "Wall.h"
#include "Player.h"
#include "Civillian.h"

class Player;

enum class GameState { PLAY, EXIT };

class Game
{
public:
	Game();
	~Game();

	void run();

	Proj42::InputManager InputManager;

private:
	void initSystems();
	void initShaders();
	void processInput();
	void drawGame();
	void updateGame();
	void gameLoop();

	int _screenWidth;
	int _screenHeight;
	float _desiredFramerate;
	float _currentFramerate;
	GameState _gameState;
	Proj42::Window _window;
	Proj42::GLSLProgram _shaderProgram;
	Proj42::Camera2D _camera;
	Proj42::SpriteBatch _spriteBatch;
	Proj42::FPSLimiter _fpsLimiter;			// really only calculates fps

	std::vector<Wall> _testwalls;
	Player* _player;
	std::vector<Civillian> _civillians;
};

