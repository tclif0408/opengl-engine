#pragma once

#include <unordered_map>

namespace Proj42 {
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		bool isKeyPressed(unsigned int keyID);

	private:
		std::unordered_map<unsigned int, bool> _keyMap;		// unordered map is built on a hashtable
	};
};
