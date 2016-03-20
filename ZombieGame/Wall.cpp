#include "Wall.h"

#include <Project42\Errors.h>
#include <Project42\ResourceManager.h>

static GLuint getWallTexture(WallType wallType)
{
	switch (wallType) {
	case WallType::BRICK:
		return Proj42::ResourceManager::getTexture("Textures/brickwall.png").id;
		break;
	case WallType::GLASS:
		return Proj42::ResourceManager::getTexture("Textures/glasswall.png").id;
		break;
	default:
		Proj42::fatalError("Couldn't find wall texture");
		return -1;
		break;
	}
}

Wall::Wall(glm::vec4 boundingBox, WallType wallType, glm::vec4 uv, float depth, Proj42::Color color)
	: Drawable(boundingBox, getWallTexture(wallType), uv, depth, color)
{
}

Wall::~Wall()
{
}
