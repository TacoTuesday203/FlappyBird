#include "Sprite.h"



Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::init(float x, float y, float w, float h, std::string texturePath) {
	//Error::log("Creating a new sprite...");

	_x = x;
	_y = y;
	_w = w;
	_h = h;

	if (_vbo == 0) {
		glGenBuffers(1, &_vbo);
	}

	_texture = TextureCache::getTexture(texturePath);

	//Error::log("Sprite successfully created.");
}

void Sprite::draw(GLubyte r, GLubyte g, GLubyte b, GLubyte a, float rotation) {

	glm::vec2 halfDims(_w / 2, _h / 2);

	glm::vec2 bl(-halfDims.x, -halfDims.y);
	//glm::vec2 bl(0.0f, 0.0f);
	glm::vec2 tl(-halfDims.x, halfDims.y);
	glm::vec2 br(halfDims.x, -halfDims.y);
	glm::vec2 tr(halfDims.x, halfDims.y);



	bl = rotatePoint(bl, rotation) + halfDims;
	br = rotatePoint(br, rotation) + halfDims;
	tl = rotatePoint(tl, rotation) + halfDims;
	tr = rotatePoint(tr, rotation) + halfDims;

	Vertex vertex[6];

	/**
	1st triangle
	**/

	//Top right
	vertex[0].setPos(_x + tr.x, _y + tr.y);
	vertex[0].setUV(1.0f, 1.0f);

	//Top left
	vertex[1].setPos(_x + tl.x, _y + tl.y);
	vertex[1].setUV(0.0f, 1.0f);

	//Bottom left
	vertex[2].setPos(_x + bl.x, _y + bl.y);
	vertex[2].setUV(0.0f, 0.0f);

	/**
	2nd triangle
	**/

	//Bottom left
	vertex[3].setPos(_x + bl.x, _y + bl.y);
	vertex[3].setUV(0.0f, 0.0f);

	//Bottom right
	vertex[4].setPos(_x + br.x, _y + br.y);
	vertex[4].setUV(1.0f, 0.0f);

	//Top right
	vertex[5].setPos(_x + tr.x, _y + tr.y);
	vertex[5].setUV(1.0f, 1.0f);

	/*Vertex vertex[6];

	// triangle 1
	vertex[0].setPos(_x, _y); // v1
	vertex[0].setUV(0.0f, 0.0f);

	vertex[1].setPos(_x, _y + _h); // v2
	vertex[1].setUV(0.0f, 1.0f);

	vertex[2].setPos(_x + _w, _y); // v3
	vertex[2].setUV(1.0f, 0.0f);

	// triangle 2
	vertex[3].setPos(_x + _w, _y); // v4
	vertex[3].setUV(1.0f, 0.0f);

	vertex[4].setPos(_x + _w, _y + _h); // v5
	vertex[4].setUV(1.0f, 1.0f);

	vertex[5].setPos(_x, _y + _h); // v6
	vertex[5].setUV(0.0f, 1.0f);*/

	for (int i = 0; i < 6; i++) {
		vertex[i].setCol(r, g, b, a);
	}

	glBindTexture(GL_TEXTURE_2D, _texture.textureID);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec2 Sprite::rotatePoint(glm::vec2 pos, float angle) {
	glm::vec2 newPos;

	angle = angle * (3.14159f / 180.0f);
	newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
	newPos.y = pos.y * cos(angle) + pos.x * sin(angle);

	return newPos;
}