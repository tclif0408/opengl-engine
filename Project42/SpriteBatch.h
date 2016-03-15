#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

#include "vertex.h"

namespace Proj42
{
	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph {
		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
		GLuint textureID;
		float depth;
	};

	class RenderBatch {
	public:
		RenderBatch(GLuint off, GLuint vertexCount, GLuint texid) :
			offset(off), numVertices(vertexCount), texture(texid) {}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		void draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, const Color& color, float depth, GLuint textureID);
		void renderBatch();
		void init();

	private:
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		void sortGlyphs();
		void createRenderBatches();
		void createVertexArray();

		GLuint _vboID;
		GLuint _vaoID;
		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;
		GlyphSortType _sortType;
	};
};
