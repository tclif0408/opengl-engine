#include "IOManager.h"

#include "Errors.h"

#include <GL/glew.h>

#include <fstream>

using namespace Proj42;

bool IOManager::readFileToBuffer(std::vector<unsigned char>& buffer, std::string filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}
	
	file.seekg(0, std::ios::end);	// seek to the end of the file	
	int fileSize = file.tellg();	// get the file size	
	file.seekg(0, std::ios::beg);	// seek back to the beginning
	
	fileSize -= file.tellg();		// reduce the file size by any header bytes that may be present (probably unnecessary)

	buffer.resize(fileSize);
	file.read((char*)&buffer[0], fileSize);		// convert from unsigned char to char

	file.close();		// file automagically closes when the object is destroyed, but it doesn't hurt to do it yourself
	return true;		// read file successfully
}
