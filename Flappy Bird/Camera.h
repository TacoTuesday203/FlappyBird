#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void init(float screenWidth, float screenHeight);
	void update();

	void setPosition(glm::vec2 pos) { _position = pos; _needsUpdate = true; }
	void setScale(float scale) { _scale = scale; _needsUpdate = true; }
	
	void addPosition(glm::vec2 pos) { _position += pos; _needsUpdate = true; }

	glm::vec2 getPos() { return _position; }
	float getScale() { return _scale; }

	glm::mat4 getCameraMatrix() { return _cameraMatrix; }

private:

	float _screenWidth;
	float _screenHeight;

	bool _needsUpdate;

	glm::vec2 _position;
	glm::mat4 _cameraMatrix;
	glm::mat4 _orthoMatrix;
	float _scale;

};

