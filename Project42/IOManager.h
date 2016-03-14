#pragma once

#include <vector>

namespace Proj42
{
	class IOManager
	{
	public:
		static bool readFileToBuffer(std::vector<unsigned char>& buffer, std::string filePath);
	};
};
