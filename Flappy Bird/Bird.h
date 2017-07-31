#pragma once

#include "Sprite.h"
#include "ShaderProgram.h"
#include "Camera.h"

#define FALL_SPEED 7.0f
#define JUMP_SPEED 0.1f

#define STARTING_POS 600.0f/2.0f-BIRD_HEIGHT/2.0f

#define BIRD_WIDTH 60.0f
#define BIRD_HEIGHT 40.0f

class Bird : public Sprite
{
public:
	Bird();
	~Bird();

	void initShader();

	void update();
	void fall();
	void jump();

	void render();

	void startJump() { _isJumping = true; _jumpTime = 100.0f; }

private:
	bool _isFalling = true;
	bool _isJumping = false;
	float _fallTime;
	float _jumpTime;

	ShaderProgram _shaderProgram;
	Camera _camera;
	//Sprite sprite;*/
};

