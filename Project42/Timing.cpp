#pragma once

#include "Timing.h"

#include <SDL/SDL.h>

using namespace Proj42;

Proj42::FPSLimiter::FPSLimiter()
{
}

void Proj42::FPSLimiter::init(float targetFPS)
{
	setTargetFPS(targetFPS);
}

void Proj42::FPSLimiter::setTargetFPS(float targetFPS)
{
	_targetFPS = targetFPS;
}

void Proj42::FPSLimiter::begin()
{
	_startTicks = SDL_GetTicks();
	calculateFPS();
}

float Proj42::FPSLimiter::end()
{
	return _fps;
}

void Proj42::FPSLimiter::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static float prevTicks = SDL_GetTicks();
	static int currentFrame = 0;

	float currentTicks, frameTimeAverage = 0.0f;
	int count;

	currentTicks = (float)SDL_GetTicks();
	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
	prevTicks = currentTicks;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	for (int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
		_fps = 1000.0f / frameTimeAverage;
	else
		_fps = 60.0f;		// just fake it
}
