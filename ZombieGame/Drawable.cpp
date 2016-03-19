#include "Drawable.h"

Drawable::Drawable(glm::vec2 position, GLuint textureID, glm::vec4 uv, float depth, Proj42::Color color)
{
	_position = position;
	_textureID = textureID;
	_uv = uv;
	_depth = depth;
	_color = color;
}

Drawable::~Drawable()
{
}

void Drawable::draw(Proj42::SpriteBatch & spriteBatch)
{
	spriteBatch.draw(_position, _uv, _color, _depth, _textureID);
}
