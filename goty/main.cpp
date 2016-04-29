#include "ZombieGame.h"

int main(int argc, char** argv)
{
	Proj42::ShaderInfo si;

	si.fragmentPath = "Shaders/colorShading.frag";
	si.vertexPath = "Shaders/colorShading.vert";

	si.attributes.push_back("vertexPosition");
	si.attributes.push_back("vertexColor");
	si.attributes.push_back("vertexUV");

	ZombieGame g = ZombieGame(1024, 768, &si);
	g.run();

	return 69;
}