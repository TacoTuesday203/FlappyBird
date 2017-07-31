#pragma once

#include <random>
#include "Sprite.h"
#include "ShaderProgram.h"
#include "Camera.h"

#define SCROLL_SPEED 5.0f

#define GAP 300.0f
#define DIST_BETWEEN_PIPES 500.0f

#define PIPE_MIN_HEIGHT 100.0f
#define PIPE_MAX_HEIGHT 200.0f

class Pipe
{
public:
	Pipe();
	~Pipe();

	void init(std::string texture, std::string textureRotated);
	void initShader();
	void update();
	void render();

	std::vector<Sprite*> getPipes() { return _pipes; }
	void clearPipes() { _pipes.clear(); }
private:
	float genRandomNumber(float rangeMin, float rangeMax);

	ShaderProgram _shaderProgram;
	Camera _camera;

	std::vector<Sprite*> _pipes;
	std::string _textureRotated;
	std::string _textureNormal;

	float _distance = 0.0f;
};

