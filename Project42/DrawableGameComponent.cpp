#include "DrawableGameComponent.h"

Proj42::DrawableGameComponent::DrawableGameComponent(glm::vec4 boundingBox, GLuint textureID, Proj42::Color color, float depth)
	: Proj42::GameComponent()
{
	_uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_color = color;
	_boundingBox = boundingBox;
	_depth = depth;
	_textureID = textureID;
}

Proj42::DrawableGameComponent::~DrawableGameComponent() { }

void Proj42::DrawableGameComponent::draw(Proj42::SpriteBatch &sb)
{
	sb.draw(_boundingBox, _uv, _color, _depth, _textureID);
}
