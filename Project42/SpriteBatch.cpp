#include "SpriteBatch.h"

#include <algorithm>

using namespace Proj42;

SpriteBatch::SpriteBatch() :
	_vboID(0),
	_vaoID(0)
{
}

SpriteBatch::~SpriteBatch()
{
}

void Proj42::SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
{
	_sortType = sortType;
	_renderBatches.clear();

	for (unsigned int i = 0; i < _glyphs.size(); i++)	// delete remaining glyphs to avoid memory leaks!
		delete _glyphs[i];

	_glyphs.clear();
}

void Proj42::SpriteBatch::end()
{
	sortGlyphs();
	createRenderBatches();
}

void Proj42::SpriteBatch::draw(const glm::vec4 & destinationRectangle, const glm::vec4 & uvRectangle, const Color & color, float depth, GLuint textureID)
{
	Glyph* newGlyph = new Glyph();
	newGlyph->depth = depth;
	newGlyph->textureID = textureID;

	// could be wrong
	newGlyph->topLeft.color = color;
	newGlyph->topLeft.setPosition(destinationRectangle.x, destinationRectangle.y + destinationRectangle.w);
	newGlyph->topLeft.setUV(uvRectangle.x, uvRectangle.y + uvRectangle.w);

	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.setPosition(destinationRectangle.x, destinationRectangle.y);
	newGlyph->bottomLeft.setUV(uvRectangle.x, uvRectangle.y);

	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.setPosition(destinationRectangle.x + destinationRectangle.z, destinationRectangle.y);
	newGlyph->bottomRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y);

	newGlyph->topRight.color = color;
	newGlyph->topRight.setPosition(destinationRectangle.x + destinationRectangle.z, destinationRectangle.y + destinationRectangle.w);
	newGlyph->topRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y + uvRectangle.w);

	_glyphs.push_back(newGlyph);
}

void Proj42::SpriteBatch::renderBatch()
{
	glBindVertexArray(_vaoID);	// set up some opengl state, binds the vertex attribute pointers and VOB

	for (unsigned int i = 0; i < _renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}

	glBindVertexArray(0);
}

void Proj42::SpriteBatch::init()
{
	createVertexArray();
}

void Proj42::SpriteBatch::createVertexArray()
{
	if (_vaoID == 0)		// generate the vao if it hasn't been already
		glGenVertexArrays(1, &_vaoID);

	glBindVertexArray(_vaoID);		// all subsequent opengl calls will modify this vao's state

	if (_vboID == 0)		// generate the vbo if it hasn't been already
		glGenBuffers(1, &_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	// tell opengl what attribute arrays we need
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	// This is the uv attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void Proj42::SpriteBatch::createRenderBatches()
{
	std::vector<Vertex> vertices;		// store all the vertices that we need to upload
	vertices.resize(_glyphs.size() * 6);	// resize the buffer to the exact size we need so we can treat it like an array

	if (_glyphs.empty()) return;

	int offset = 0;		// current offset
	int cv = 0;		// current vertex

	// add the first batch
	_renderBatches.emplace_back(offset, 6, _glyphs[0]->textureID);
	vertices[cv++] = _glyphs[0]->topLeft;
	vertices[cv++] = _glyphs[0]->bottomLeft;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->topRight;
	vertices[cv++] = _glyphs[0]->topLeft;
	offset += 6;

	// add the rest of the glyphs
	for (unsigned int cg = 1; cg < _glyphs.size(); cg++)
	{
		// check if this glyph can be part of the current batch
		// make a new batch if it isn't, increment numVertices if it is
		if (_glyphs[cg]->textureID != _glyphs[cg - 1]->textureID)
			_renderBatches.emplace_back(offset, 6, _glyphs[cg]->textureID);
		else
			_renderBatches.back().numVertices += 6;

		vertices[cv++] = _glyphs[cg]->topLeft;
		vertices[cv++] = _glyphs[cg]->bottomLeft;
		vertices[cv++] = _glyphs[cg]->bottomRight;
		vertices[cv++] = _glyphs[cg]->bottomRight;
		vertices[cv++] = _glyphs[cg]->topRight;
		vertices[cv++] = _glyphs[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);		// bind vbo
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);	// orphan the buffer (for speed)
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());		// upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);		// unbind the vbo
}

bool Proj42::SpriteBatch::compareFrontToBack(Glyph * a, Glyph * b)
{
	return a->depth < b->depth;
}

bool Proj42::SpriteBatch::compareBackToFront(Glyph * a, Glyph * b)
{
	return a->depth > b->depth;
}

bool Proj42::SpriteBatch::compareTexture(Glyph * a, Glyph * b)
{
	return a->textureID < b->textureID;
}

void Proj42::SpriteBatch::sortGlyphs()
{
	switch (_sortType) {
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
		break;
	}
}
