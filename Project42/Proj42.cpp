#include "Proj42.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

namespace Proj42
{
	int init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);						// initialize SDL
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);		// tell opengl/sdl we want to double buffer
		return 0;
	}
};