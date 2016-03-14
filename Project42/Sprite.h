#pragma once

#include <string>

#include <GL/glew.h>

#include "ResourceManager.h"

namespace Proj42
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void draw();
		void init(float x, float y, float width, float height, const std::string& texturePath);

	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;
		GLTexture _texture;
	};
};
