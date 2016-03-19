#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

namespace Proj42 {
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void setMouseCoords(float x, float y);
		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		bool isKeyPressed(unsigned int keyID);

		glm::vec2 getMouseCoords() const { return _mouseCoords; }

	private:
		std::unordered_map<unsigned int, bool> _keyMap;		// unordered map is built on a hashtable
		glm::vec2 _mouseCoords;
	};
};
