#pragma once

#include "Sprite.h"
#include "ShaderProgram.h"
#include "Camera.h"

class Dead : public Sprite
{
public:
	Dead();
	~Dead();

	void initShader();
	void update();
	void render();
private:
	ShaderProgram _shaderProgram;
	Camera _camera;
};

