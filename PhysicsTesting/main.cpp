#include <iostream>
#include "PhysicsTest.h"

int main(int argc, char** argv)
{
	Proj42::ShaderInfo si;

	si.fragmentPath = "";
	si.vertexPath = "";

	si.attributes.push_back("");
	si.attributes.push_back("");
	si.attributes.push_back("");

	PhysicsTest pt = PhysicsTest(1024, 768, si);
	pt.run();

	return 0;
}