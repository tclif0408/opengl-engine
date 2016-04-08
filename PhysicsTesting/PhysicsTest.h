#pragma once

#include <Project42\Window.h>
#include <Project42\GLSLProgram.h>
#include <Project42\SpriteBatch.h>
#include <Project42\Camera2D.h>
#include <Project42\InputManager.h>
#include <Project42\Timing.h>

#include "PhysicsObject.h"

enum class State { PLAY, EXIT };

class PhysicsTest
{
public:
	PhysicsTest();
	~PhysicsTest();

	void run();

private:
	void gameLoop();
	void initSystems();
	void initShaders();
	void processInput();
	void drawGame();
	void update();

	Proj42::Window _window;
	Proj42::GLSLProgram _shaderProgram;
	Proj42::Camera2D _camera;
	Proj42::SpriteBatch _spriteBatch;
	Proj42::FPSLimiter _fpsLimiter;
	Proj42::InputManager _inputManager;
	State _state;
	int _screenWidth;
	int _screenHeight;
	float _maxFPS;
	float _framerate;

	std::vector<PhysicsObject> _physObjs;
};

