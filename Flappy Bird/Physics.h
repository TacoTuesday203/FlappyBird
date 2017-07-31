#pragma once

#include "Bird.h"
#include "Pipe.h"

class Physics
{
public:
	static bool collision(std::vector<Sprite*> pipes, Bird bird);
};

