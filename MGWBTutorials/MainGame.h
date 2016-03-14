#pragma once

#include <SDL/sdl.h>
#include <GL/glew.h>

#include <vector>

#include <Project42/Sprite.h>
#include <Project42/GLSLProgram.h>
#include <Project42/GLTexture.h>
#include <Project42/Window.h>
#include <Project42/Camera2D.h>

const float MAX_FPS = 60.0f;

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
	std::vector<Proj42::Sprite*> _sprites;
	Proj42::GLSLProgram _colorProgram;
	float _time;
	float _fps;
	float _frameTime;
	Proj42::Camera2D _camera;
};

