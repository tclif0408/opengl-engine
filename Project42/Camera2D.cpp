#include "Camera2D.h"

using namespace Proj42;

Camera2D::Camera2D() :
	_position(0.0f, 0.0f),
	_cameraMatrix(1.0f),
	_orthoMatrix(1.0f),
	_needsMatrixUpdate(true),
	_scale(1.0f),
	_screenWidth(800),
	_screenHeight(600)
{
}

Camera2D::~Camera2D()
{
}

void Proj42::Camera2D::update()
{
	if (_needsMatrixUpdate)
	{
		glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
		glm::vec3 scale(_scale, _scale, 0.0f);

		_cameraMatrix = glm::translate(_orthoMatrix, translate);					// camera translation
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;			// camera scale

		_needsMatrixUpdate = false;		// the matrix no longer needs to be updated
	}
}

void Proj42::Camera2D::init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

glm::vec2 Proj42::Camera2D::convertScreenToWorldCoords(glm::vec2 screenCoords)
{
	// invert y
	screenCoords.y = _screenHeight - screenCoords.y;
	// make the center of the screen the origin
	screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
	// account for scale
	screenCoords /= _scale;
	// translate based on camera
	screenCoords += _position;

	return screenCoords;
}
