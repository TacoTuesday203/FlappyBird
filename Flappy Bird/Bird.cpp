#include "Bird.h"



Bird::Bird()
{
}


Bird::~Bird()
{
}

void Bird::initShader() {
	_shaderProgram.createShaders("shaders/bird.vert", "shaders/bird.frag");
	_shaderProgram.bindAttrib("vert_Pos");
	_shaderProgram.bindAttrib("vert_Col");
	_shaderProgram.bindAttrib("vert_UV");
	_shaderProgram.linkShaders();
	_camera.init(1024, 600);
}

void Bird::update() {
	_camera.update();
	fall();
	jump();
}

void Bird::fall() {
	if (_isFalling && !_isJumping) {
		_fallTime += 0.1f;
		if (getY() - FALL_SPEED*_fallTime < 100.0f) {
			setY(100.0f);
			_isFalling = false;
			_fallTime = 0;
			return;
		}
		addY(-(FALL_SPEED*_fallTime));
	}
}

void Bird::jump() {
	if (_isJumping) {

		if (_fallTime != 0.0f)
			_fallTime = 0.0f;

		if (_jumpTime <= 0.0f) {
			_isJumping = false;
			_isFalling = true;
			return;
		}

		_jumpTime -= 5.0f;

		if (getY() >= 600.0f - getH()) {
			setY(600.0f - getH());
			_isJumping = false;
			_isFalling = true;
			return;
		}

		addY(JUMP_SPEED*_jumpTime);
	}
}

void Bird::render() {
	_shaderProgram.use();

	glUniform1i(_shaderProgram.getUniformLocation("textureUniform"), 0);
	glUniformMatrix4fv(_shaderProgram.getUniformLocation("camera"), 1, GL_FALSE, &_camera.getCameraMatrix()[0][0]);

	if (!(getY() <= 100.0f)) {
		draw(255, 255, 255, 255, -_fallTime * 30.0f + 20.0f);
	}
	else {
		draw(255, 255, 255, 255, -90.0f);
	}

	_shaderProgram.unuse();
}