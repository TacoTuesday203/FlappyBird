#include "Pipe.h"



Pipe::Pipe()
{
}


Pipe::~Pipe()
{
}

void Pipe::init(std::string textureNormal, std::string textureRotated) {
	int y = genRandomNumber(PIPE_MIN_HEIGHT, PIPE_MAX_HEIGHT);
	_pipes.push_back(new Sprite());
	_pipes.back()->init(1024.0f + 200.0f, 100.0f - 600.0f + y, 125.0f, 600.0f, textureNormal);
	_pipes.push_back(new Sprite());
	_pipes.back()->init(1024.0f + 200.0f, y + GAP, 125.0f, 600.0f, textureRotated);
	_textureNormal = textureNormal;
	_textureRotated = textureRotated;
}

void Pipe::initShader() {
	_shaderProgram.createShaders("shaders/pipe.vert", "shaders/pipe.frag");
	_shaderProgram.bindAttrib("vert_Pos");
	_shaderProgram.bindAttrib("vert_Col");
	_shaderProgram.bindAttrib("vert_UV");
	_shaderProgram.linkShaders();
	_camera.init(1024, 600);
}

void Pipe::update() {
	_camera.update();
	_distance+=SCROLL_SPEED;
	if (_distance >= DIST_BETWEEN_PIPES) {
		int y = genRandomNumber(PIPE_MIN_HEIGHT, PIPE_MAX_HEIGHT);
		_pipes.push_back(new Sprite());
		_pipes.back()->init(1024.0f + 200.0f, 100.0f - 600.0f + y, 125.0f, 600.0f, _textureNormal);
		_pipes.push_back(new Sprite());
		_pipes.back()->init(1024.0f + 200.0f, y + GAP, 125.0f, 600.0f, _textureRotated);
		_distance = 0.0f;
	}
	for (int i = 0; i < _pipes.size(); i++) {
		if (_pipes[i]->getX() + _pipes[i]->getW() <= 0.0f) {
			_pipes.erase(_pipes.begin() + i);
			continue;
		}
		_pipes[i]->addX(-SCROLL_SPEED);
	}
}

void Pipe::render() {
	_shaderProgram.use();

	glUniform1i(_shaderProgram.getUniformLocation("textureUniform"), 0);
	glUniformMatrix4fv(_shaderProgram.getUniformLocation("camera"), 1, GL_FALSE, &_camera.getCameraMatrix()[0][0]);

	for (int i = 0; i < _pipes.size(); i++) {
		_pipes[i]->draw();
	}

	_shaderProgram.unuse();
}

float Pipe::genRandomNumber(float rangeMin, float rangeMax) {
	std::default_random_engine generator;
	std::uniform_real_distribution<float> dist(rangeMin, rangeMax);
	float rand = dist(std::random_device{});
	return rand;
}