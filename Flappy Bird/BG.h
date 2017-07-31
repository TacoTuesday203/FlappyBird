#pragma once

#include "ShaderProgram.h"
#include "Camera.h"
#include "Sprite.h"

class BG : public Sprite
{
public:
	BG();
	~BG();

	void initShader();
	void update();
	void render();

private:
	ShaderProgram _shaderProgram;
	Camera _camera;
};

