#pragma once

#include <Project42\Game.h>
#include "PhysicsObject.h"

class PhysicsTest : public Proj42::Game {

public:
	PhysicsTest(int windowWidth, int windowHeight, std::string* fragmentFilePath, std::string* vertexFilePath, std::vector<std::string*>* shaderAttributes)
		: Proj42::Game(windowWidth, windowHeight, fragmentFilePath, vertexFilePath, shaderAttributes) {}
	~PhysicsTest() {}
	
private:
	void initialize();
	void update();
	void draw();

	std::vector<PhysicsObject> _physicsObjects;

};
