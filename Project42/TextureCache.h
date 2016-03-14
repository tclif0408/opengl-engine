#pragma once

#include "GLTexture.h"

#include <map>

namespace Proj42
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(const std::string& filePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
};