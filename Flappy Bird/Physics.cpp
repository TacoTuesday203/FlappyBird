#include "Physics.h"

bool Physics::collision(std::vector<Sprite*> pipes, Bird bird) {
	for (int i = 0; i < pipes.size(); i++) {
		if (i % 2 != 0) {
			if (bird.getX() + bird.getW() >= pipes[i]->getX() && bird.getY() + bird.getH() >= pipes[i]->getY() && bird.getX() <= pipes[i]->getX() + pipes[i]->getW()) {
				return true;
			}
		}
		else if (i % 2 == 0 || i == 0) {
			if (bird.getX() + bird.getW() >= pipes[i]->getX() && bird.getY() <= pipes[i]->getY() + pipes[i]->getH() && bird.getX() <= pipes[i]->getX() + pipes[i]->getW() && bird.getY() <= pipes[i]->getH()) {
				return true;
			}
		}
	}
	return false;
}