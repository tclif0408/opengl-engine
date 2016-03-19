#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Proj42
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void update();
		void init(int screenWidth, int screenHeight);

		glm::vec2 convertScreenToWorldCoords(glm::vec2 screenCoords);

		// setters
		void setPosition(const glm::vec2& position) { _position = position; _needsMatrixUpdate = true; }
		void setScale(float scale) { _scale = scale; _needsMatrixUpdate = true; }

		// getters
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }
		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		
	private:
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		float _scale;
		bool _needsMatrixUpdate;
		int _screenWidth;
		int _screenHeight;
	};
};
