#pragma once

#include "TextureCache.h"

namespace Proj42
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(const std::string& filePath);

	private:
		static TextureCache _textureCache;
	};
};
