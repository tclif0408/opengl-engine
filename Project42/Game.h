#pragma once

#include "Proj42.h"

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

	class Game
	{
	public:
		Game(int windowWidth, int windowHeight, std::string* fragmentFilePath, std::string* vertexFilePath, std::vector<std::string*>* shaderAttributes);
		~Game();

		void run();

	protected:
		bool isKeyPressed(unsigned int keyID) { return _inputManager.isKeyPressed(keyID); }
		glm::vec2 CenterScreen() { return glm::vec2(_screenWidth / 2.0f, _screenHeight / 2.0f); }
		GLuint getTextureID(const std::string& filePath) { ResourceManager::getTexture(filePath).id; }
		int getFrameRate() { return _currentFramerate; }

		void setCameraPos(glm::vec2 val) { _camera.setPosition(val); }
		void setDesiredFPS(float value) { _maxFPS = value; }
		void addGameComponent(GameComponent component) { _components.push_back(component); }

		virtual void initialize() {}
		virtual void update();
		virtual void draw();

		GameState _gameState;
		int _screenWidth;
		int _screenHeight;
		Proj42::Window _window;
		std::string _windowTitle;
		unsigned int _windowFlags;

	private:
		void endDraw();
		void gameLoop();
		void initShaders();
		void initSystems();
		void processInput();
		void setUpDraw();

		float _currentFramerate;
		float _maxFPS;
		Proj42::Camera2D _camera;
		Proj42::FPSLimiter _fpsLimiter;
		Proj42::InputManager _inputManager;
		Proj42::GLSLProgram _shaderProgram;
		Proj42::SpriteBatch _spriteBatch;
		std::string* _fragmentFilePath;
		std::string* _vertexFilePath;
		std::vector<std::string*>* _shaderAttributes;
		std::vector<GameComponent> _components;

	};

};