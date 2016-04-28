#pragma once

#include "Game.h"
#include "GameComponent.h"

namespace Proj42 {

	class DrawableGameComponent : public GameComponent {

	public:
		DrawableGameComponent(Game* game, glm::vec4 boundingBox, GLuint textureID, Proj42::Color color = Proj42::Color(255, 255, 255, 255), float depth = 0.0f);
		~DrawableGameComponent();

		void setPosition(glm::vec2 value) { _boundingBox.x = value.x; _boundingBox.y = value.y; }
		glm::vec2 getPosition() { return glm::vec2(_boundingBox.x, _boundingBox.y); }

		void draw(Proj42::SpriteBatch &sb);
		glm::vec4 getBoundingBox() { return _boundingBox; }

	private:
		glm::vec4 _uv;
		glm::vec4 _boundingBox;
		GLuint _textureID;
		float _depth;
		Proj42::Color _color;
	};

};