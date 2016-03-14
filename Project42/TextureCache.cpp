#include "TextureCache.h"

#include "ImageLoader.h"

#include <iostream>

using namespace Proj42;

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(const std::string & filePath)
{
	// look up the texture and see if its in the map
	auto mapIterator = _textureMap.find(filePath);

	// check if its not in the map
	if (mapIterator == _textureMap.end())
	{// if it isn't there, load it and insert it into the map
		GLTexture newTexture = ImageLoader::loadPNG(filePath);
		_textureMap.insert(std::make_pair(filePath, newTexture));

		std::cout << "Loaded texture! :D\n";
		return newTexture;
	}

	// if it is in the map, return it
	std::cout << "Used cached texture! :D\n";
	return mapIterator->second;
}
