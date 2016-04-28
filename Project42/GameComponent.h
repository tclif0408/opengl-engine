#pragma once

#include "Game.h"

namespace Proj42 {

	class GameComponent
	{
	public:
		GameComponent(Game* game);
		~GameComponent() {}
		virtual void update() {}
	};

};
