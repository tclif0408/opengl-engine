#pragma once

#include <GL/glew.h>

namespace Proj42
{
	struct Position { // 8 bytes
		float x;
		float y;
	};

	struct Color {	// 4 bytes
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV {
		float u;
		float v;
	};

	// size in bytes must be a multiple of 4
	struct Vertex {
		Position position;
		Color color;
		UV uv;					// uv texture coordinates

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
};