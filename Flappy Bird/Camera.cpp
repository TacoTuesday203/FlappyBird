#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::init(float screenWidth, float screenHeight) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_position = glm::vec2(0.0f, 0.0f);
	_scale = 1.0f;
	_needsUpdate = true;

	_cameraMatrix = glm::mat4(1.0f);
	_orthoMatrix = glm::ortho(0.0f, _screenWidth, 0.0f, _screenHeight);
}

void Camera::update() {
	if (_needsUpdate) {
		glm::vec3 translate(-_position.x, -_position.y, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);

		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0), scale) * _cameraMatrix;
		_needsUpdate = false;
	}
}