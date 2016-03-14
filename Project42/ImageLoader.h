#pragma once

#include "GLTexture.h"

#include <string>

namespace Proj42
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(const std::string& filePath);
	};
};

