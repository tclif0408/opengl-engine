#pragma once

#include <iostream>
#include <Project42\Game.h>
#include "PhysicsObject.h"

class PhysicsTest : public Proj42::Game {

public:
	PhysicsTest(int windowWidth, int windowHeight, Proj42::ShaderInfo* shaderInfo)
		: Proj42::Game(windowWidth, windowHeight, shaderInfo) {}
	~PhysicsTest() {}
	
private:
	void initialize();
	void update();
	void draw();

	std::vector<PhysicsObject> _physicsObjects;

};
