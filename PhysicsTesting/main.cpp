#include <iostream>
#include "PhysicsTest.h"
using namespace Proj42;

int main(int argc, char** argv)
{
	ShaderInfo si;

	si.fragmentPath = "Shaders/colorShading.frag";
	si.vertexPath = "Shaders/colorShading.vert";

	si.attributes.push_back("vertexPosition");
	si.attributes.push_back("vertexColor");
	si.attributes.push_back("vertexUV");

	PhysicsTest pt = PhysicsTest(1024, 768, &si);
	pt.run();

	return 42;
}