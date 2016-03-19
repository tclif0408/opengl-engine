#include "InputManager.h"

using namespace Proj42;

InputManager::InputManager() :
	_mouseCoords(0.0f)
{
}

InputManager::~InputManager()
{
}

void Proj42::InputManager::setMouseCoords(float x, float y)
{
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

void Proj42::InputManager::pressKey(unsigned int keyID)
{
	_keyMap[keyID] = true;
}

void Proj42::InputManager::releaseKey(unsigned int keyID)
{
	_keyMap[keyID] = false;
}

bool Proj42::InputManager::isKeyPressed(unsigned int keyID)
{
	auto iterator = _keyMap.find(keyID);
	if (iterator != _keyMap.end())
		return _keyMap[keyID];
	return false;
}
