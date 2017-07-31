#pragma once

#include <glew.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "Error.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void createShaders(const std::string vertFilePath, const std::string fragFilePath);
	void linkShaders();

	void use();
	void unuse();

	void bindAttrib(std::string attribName);

	GLint getUniformLocation(std::string uniform);

	// getters

	GLint getShaderProgram() { return _shaderProgram; }

private:

	void compileShader(std::string path, GLuint shader);

	GLint _shaderProgram;

	GLuint _vertShader;
	GLuint _fragShader;

	int _numAttribs = 0;

};

