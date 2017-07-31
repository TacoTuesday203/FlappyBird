#pragma once

#include <glew.h>
#include <glm.hpp>
#include "Error.h"
#include "Vertex.h"
#include "TextureCache.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float w, float h, std::string texturePath);
	void draw(GLubyte r = 255, GLubyte g = 255, GLubyte b = 255, GLubyte a = 255, float rotation = 0.0f);

	void addX(float x) { _x += x; }
	void addY(float y) { _y += y; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	float getX() { return _x; }
	float getY() { return _y; }
	float getW() { return _w; }
	float getH() { return _h; }

private:
	float _x;
	float _y;
	float _w;
	float _h;
	GLuint _vbo = 0;
	Texture _texture;

	glm::vec2 rotatePoint(glm::vec2 pos, float angle);
};

