#pragma once

#include <Project42\Game.h>
#include <Project42\Keys.h>

#include "Player.h"

class ZombieGame : public Proj42::Game
{
public:
	ZombieGame(int w, int h, Proj42::ShaderInfo* si)
		: Proj42::Game(w, h, si) {}
	~ZombieGame()
	{
		delete _player;
	}

private:
	void initialize();
	void update();

	Player* _player;
};

