#pragma once

#include <Project42\SpriteBatch.h>

static glm::vec4 GLOBAL_UV() { return glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); }

static float GLOBAL_DEPTH() { return 1.0f; }

static Proj42::Color WHITE()
{
	Proj42::Color white;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;
	return white;
}


class Drawable
{
public:
	Drawable(glm::vec4 boundingBox, GLuint textureID, glm::vec4 uv = GLOBAL_UV(), float depth = GLOBAL_DEPTH(), Proj42::Color color = WHITE());
	~Drawable();

	void draw(Proj42::SpriteBatch& spriteBatch);

	glm::vec4 getBoundingBox() { return _boundingBox; }

protected:
	glm::vec4 _boundingBox;
	glm::vec4 _uv;
	GLuint _textureID;
	float _depth;
	Proj42::Color _color;
};

