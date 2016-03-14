#include "ResourceManager.h"

using namespace Proj42;

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(const std::string & filePath)
{
	return _textureCache.getTexture(filePath);
}
