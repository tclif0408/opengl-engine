#pragma once

#include <vector>
#include <string>

#include "Camera2D.h"
#include "DrawableGameComponent.h"
#include "GLSLProgram.h"
#include "InputManager.h"
#include "Timing.h"
#include "ResourceManager.h"
#include "SpriteBatch.h"
#include "Window.h"

namespace Proj42 {

	enum class GameState { PLAY, EXIT };

	struct ShaderInfo {
		std::string fragmentPath;
		std::string vertexPath;
		std::vector<std::string> attributes;
	};

	class Game
	{
	public:
		Game(int windowWidth, int windowHeight, ShaderInfo* shaderInfo);
		~Game();

		void run();

	protected:
		glm::vec2 CenterScreen() { return glm::vec2(_screenWidth / 2.0f, _screenHeight / 2.0f); }
		GLuint getTextureID(const std::string& filePath) { return ResourceManager::getTexture(filePath).id; }
		float getFrameRate() { return _currentFramerate; }

		void setCameraPos(glm::vec2 val) { _camera.setPosition(val); }
		void setDesiredFPS(float value) { _maxFPS = value; }
		void addGameComponent(GameComponent* component) { _components.push_back(component); }
		void setGameState(GameState state) { _gameState = state; }

		virtual void initialize() {}
		virtual void update();
		virtual void draw();

		int _screenWidth;
		int _screenHeight;
		Proj42::Window _window;
		std::string _windowTitle;
		unsigned int _windowFlags;
		Proj42::InputManager _inputManager;

	private:
		void endDraw();
		void gameLoop();
		void initShaders();
		void initSystems();
		void processInput();
		void setUpDraw();

		GameState _gameState;
		float _currentFramerate;
		float _maxFPS;
		Proj42::Camera2D _camera;
		Proj42::FPSLimiter _fpsLimiter;
		Proj42::GLSLProgram _shaderProgram;
		Proj42::SpriteBatch _spriteBatch;
		ShaderInfo* _shaderInfo;
		std::vector<GameComponent*> _components;

	};

};