#pragma once

#include "Sprite.h"
#include "ShaderProgram.h"
#include "Camera.h"

#define SCROLL_SPEED 5.0f

class Floor
{
public:
	Floor();
	~Floor();

	void init(float x, float y, float w, float h, std::string texture);
	void initShader();
	void update();
	void render();

private:
	std::vector<Sprite*> _floors;

	float _w;
	float _h;
	std::string _texturePath;

	ShaderProgram _shaderProgram;
	Camera _camera;
};

