#pragma once

#include <glew.h>

struct Position {
	float x;
	float y;
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV {
	float u;
	float v;
};

struct Vertex {
	Position pos;
	Color col;
	UV uv;
	void setPos(float x, float y) { pos.x = x; pos.y = y; }
	void setCol(GLubyte r, GLubyte g, GLubyte b, GLubyte a) { col.r = r; col.g = g; col.b = b; col.a = a; }
	void setUV(float u, float v) { uv.u = u; uv.v = v; }
};