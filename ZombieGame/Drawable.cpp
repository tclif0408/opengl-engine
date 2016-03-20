#include "Drawable.h"

Drawable::Drawable(glm::vec4 boundingBox, GLuint textureID, glm::vec4 uv, float depth, Proj42::Color color)
{
	_boundingBox = boundingBox;
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
	spriteBatch.draw(_boundingBox, _uv, _color, _depth, _textureID);
}
