#include "BG.h"



BG::BG()
{
}


BG::~BG()
{
}

void BG::initShader() {
	_shaderProgram.createShaders("shaders/bg.vert", "shaders/bg.frag");
	_shaderProgram.bindAttrib("vert_Pos");
	_shaderProgram.bindAttrib("vert_Col");
	_shaderProgram.bindAttrib("vert_UV");
	_shaderProgram.linkShaders();
	_camera.init(1024, 600);
}

void BG::update() {
	_camera.update();
}

void BG::render() {
	_shaderProgram.use();

	glUniform1i(_shaderProgram.getUniformLocation("textureUniform"), 0);
	glUniformMatrix4fv(_shaderProgram.getUniformLocation("camera"), 1, GL_FALSE, &_camera.getCameraMatrix()[0][0]);

	draw();

	_shaderProgram.unuse();
}