#include "Window.h"

#include "Errors.h"

using namespace Proj42;

Window::Window()
{
}

Window::~Window()
{
}

int Window::create(std::string windowTitle, int screenWidth, int screenHeight, unsigned int userFlags)
{
	Uint32 flags = SDL_WINDOW_OPENGL;
	SDL_GLContext glContext;

	if (userFlags & INVISIBLE)
		flags |= SDL_WINDOW_HIDDEN;
	if (userFlags & FULLSCREEN)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (userFlags & BORDERLESS)
		flags |= SDL_WINDOW_BORDERLESS;

	// create SDL window
	_sdlWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
	if (_sdlWindow == nullptr)
		fatalError("failed to create SDL window! D:");

	// create OpenGL context
	glContext = SDL_GL_CreateContext(_sdlWindow);
	if (glContext == nullptr)
		fatalError("SDL_GL context could not be created! :(");

	// initialize GLEW
	if (glewInit() != GLEW_OK)
		fatalError("Failed to initialize GLEW! >:/");

	// check the user's opengl version
	printf("*** OPENGL VERSION: %s ***\n", glGetString(GL_VERSION));

	glClearColor(0.3f, 1.0f, 1.0f, 1.0f);				// set background clear color
	SDL_GL_SetSwapInterval(1);							// enable VSYNC

	return 0;											// everything is okay! ;D
}

void Window::swapBuffer()
{
	SDL_GL_SwapWindow(_sdlWindow);
}
