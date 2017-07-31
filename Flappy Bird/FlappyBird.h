#pragma once
#pragma once

#include <SDL.h>
#include <glew.h>

#include "Error.h"
#include "Bird.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "BG.h"
#include "Floor.h"
#include "Pipe.h"
#include "Dead.h"
#include "Physics.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

enum class GameState {
	PLAY, STOP
};

class FlappyBird
{
public:
	FlappyBird();
	~FlappyBird();

	void init();
	void gameLoop();
	void processInput();
	void render();

private:
	SDL_Window* _window;
	GameState _gameState;
	Bird _bird;
	BG _bg;
	Floor _floor;
	Pipe _pipe;
	Dead _deathMsg;

	bool _dead = false;
};

