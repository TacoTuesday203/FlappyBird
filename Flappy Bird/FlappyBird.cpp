#include "FlappyBird.h"



FlappyBird::FlappyBird()
{
}


FlappyBird::~FlappyBird()
{
}

void FlappyBird::init() {
	Error::log("Flappy Bird RELEASE 1.2.1 by Josh");
	Error::log("Initializing...");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		Error::crash("Unable to start SDL", 1);
	}
	_window = nullptr;
	_window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		Error::crash("Unable to create SDL window", 2);
	}
	SDL_GLContext context = SDL_GL_CreateContext(_window);
	if (context == nullptr) {
		Error::crash("Unable to create GL context", 3);
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (glewInit() != GLEW_OK) {
		Error::crash("Unable to start GLEW", 4);
	}
	Error::log("Initialization completed.");
	glClearColor(222/255, 216/255, 149/255, 1.0f);
	_gameState = GameState::PLAY;

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_bird.init(250.0f, SCREEN_HEIGHT/2.0f-BIRD_HEIGHT/2.0f, BIRD_WIDTH, BIRD_HEIGHT, "textures/bird.png");
	_bird.initShader();
	
	_bg.init(0.0f, 100.0f, SCREEN_WIDTH, SCREEN_HEIGHT- 100.0f, "textures/bg.png");
	_bg.initShader();

	_floor.init(0.0f, 0.0f, SCREEN_WIDTH, 100.0f, "textures/floor.png");
	_floor.initShader();

	_pipe.init("textures/pipe.png", "textures/pipe_rotated.png");
	_pipe.initShader();

	_deathMsg.init(512.0f - 100.0f, 300.0f - 25.0f, 200.0f, 50.0f, "textures/dead.png");
	_deathMsg.initShader();
}

void FlappyBird::gameLoop() {
	while (_gameState == GameState::PLAY) {
		_bird.update();
		if (!_dead) {
			_bg.update();
			_floor.update();
			_pipe.update();
		}
		else {
			_deathMsg.update();
		}

		if (Physics::collision(_pipe.getPipes(), _bird) == true || _bird.getY() <= 100.0f) {
			_dead = true;
		}

		processInput();
		render();
	}
	if (_gameState == GameState::STOP) {
		Error::log("Goodbye!");
		return;
	}
}

void FlappyBird::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			Error::log("Quit command received!");
			_gameState = GameState::STOP;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (!_dead) {
				_bird.startJump();
			}
			else {
				if (_bird.getY() <= 100.0f) {
					_dead = false;
					_pipe.clearPipes();
					_bird.setY(STARTING_POS);
				}
			}
			break;
		}
	}
}

void FlappyBird::render() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);

	_bg.render();
	_pipe.render();
	_bird.render();
	_floor.render();
	if (_dead) {
		_deathMsg.render();
	}

	SDL_GL_SwapWindow(_window);
}

int main(int argc, char* argv[]) {
	FlappyBird f;
	f.init();
	f.gameLoop();
	return 0;
}