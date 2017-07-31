#include "Dead.h"



Dead::Dead()
{
}


Dead::~Dead()
{
}

void Dead::initShader() {
	_shaderProgram.createShaders("shaders/dead.vert", "shaders/dead.frag");
	_shaderProgram.bindAttrib("vert_Pos");
	_shaderProgram.bindAttrib("vert_Col");
	_shaderProgram.bindAttrib("vert_UV");
	_shaderProgram.linkShaders();
	_camera.init(1024, 600);
}

void Dead::update() {
	_camera.update();
}

void Dead::render() {
	_shaderProgram.use();
	
	glUniform1i(_shaderProgram.getUniformLocation("textureUniform"), 0);
	glUniformMatrix4fv(_shaderProgram.getUniformLocation("camera"), 1, GL_FALSE, &_camera.getCameraMatrix()[0][0]);

	draw();

	_shaderProgram.unuse();
}