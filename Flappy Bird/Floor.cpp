#include "Floor.h"



Floor::Floor()
{
}


Floor::~Floor()
{
}

void Floor::init(float x, float y, float w, float h, std::string texture) {
	for (int i = 0; i < 2; i++) {
		_floors.push_back(new Sprite());
		_floors.back()->init(i * w, y, w, h, texture);
		_w = w;
		_h = h;
		_texturePath = texture;
	}
	/*_floors.push_back(new Sprite());
	_floors.back()->init(200.0f, 0.0f, 1024.0f, 100.0f, texture);
	_floors.push_back(new Sprite());
	_floors.back()->init(1224.0f, 0.0f, 1024.0f, 100.0f, texture);*/
}

void Floor::initShader() {
	_shaderProgram.createShaders("shaders/floor.vert", "shaders/floor.frag");
	_shaderProgram.bindAttrib("vert_Pos");
	_shaderProgram.bindAttrib("vert_Col");
	_shaderProgram.bindAttrib("vert_UV");
	_shaderProgram.linkShaders();
	_camera.init(1024, 600);
}

void Floor::update() {
	_camera.update();
	for (int i = 0; i < _floors.size(); i++) {
		if (_floors[i]->getX() + _floors[i]->getW() < 0.0f) {
			_floors.push_back(new Sprite());
			_floors.back()->init(_w, 0.0f, _w + 1.0f, _h, _texturePath);
			_floors.erase(_floors.begin() + i);
			continue;
		}
		_floors[i]->addX(-SCROLL_SPEED);
	}
}

void Floor::render() {
	_shaderProgram.use();

	glUniform1i(_shaderProgram.getUniformLocation("textureUniform"), 0);
	glUniformMatrix4fv(_shaderProgram.getUniformLocation("camera"), 1, GL_FALSE, &_camera.getCameraMatrix()[0][0]);

	for (int i = 0; i < _floors.size(); i++) {
		_floors[i]->draw();
	}
	//_floors[0]->draw();

	_shaderProgram.unuse();
}