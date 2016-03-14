#include "Errors.h"

#include <iostream>
#include <cstdlib>

#include <SDL\SDL.h>

namespace Proj42
{
	void fatalError(std::string message) {
		std::cout << message << std::endl;
		std::cout << "Enter any key to continue..." << std::endl;

		int a;
		std::cin >> a;
		SDL_Quit();
		exit(420);
	}
};