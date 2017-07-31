#include "ShaderProgram.h"



ShaderProgram::ShaderProgram()
{
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::createShaders(const std::string vertFilePath, const std::string fragFilePath) {

	Error::log("Creating shaders (" + vertFilePath + ")" + ", (" + fragFilePath + ")");

	_shaderProgram = glCreateProgram();

	_vertShader = glCreateShader(GL_VERTEX_SHADER);
	_fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	compileShader(vertFilePath, _vertShader);
	compileShader(fragFilePath, _fragShader);

	//Error::log("Successfully created shader program");

}
void ShaderProgram::linkShaders() {

	Error::log("Linking shaders...");

	glAttachShader(_shaderProgram, _vertShader);
	glAttachShader(_shaderProgram, _fragShader);

	glLinkProgram(_shaderProgram);

	GLchar* programInfoLog;
	int programIsCompiled = 0;

	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, (int*)&programIsCompiled);
	if (programIsCompiled == 0) {
		int maxLength;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		programInfoLog = (char*)malloc(maxLength);

		glGetProgramInfoLog(_shaderProgram, maxLength, &maxLength, programInfoLog);

		Error::error("The following errors occurred while linking shaders...", 4);
		std::cout << programInfoLog << std::endl << std::endl;
		Error::crash("Fall! had to crash due to an error with shaders.", 4);

	}

	//Error::log("Shaders successfully linked! Cleaning up...");

	glDetachShader(_shaderProgram, _vertShader);
	glDetachShader(_shaderProgram, _fragShader);

	//Error::log("Done cleaning");
}

void ShaderProgram::compileShader(std::string path, GLuint shader) {

	std::string shaderSrc;
	std::string line;

	std::ifstream loadShader(path);
	if (loadShader.fail()) {
		Error::crash("Unable to find shader @" + path, 5);
	}

	while (!loadShader.eof()) {
		std::getline(loadShader, line);
		shaderSrc += line + "\n";
	}

	const char* shaderSrcPtr = shaderSrc.c_str();

	glShaderSource(shader, 1, &shaderSrcPtr, nullptr);

	glCompileShader(shader);

	GLchar* infoLog;
	int isCompiled = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == 0) {
		int maxLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		infoLog = (char*)malloc(maxLength);

		glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

		Error::error("Shader " + path + " has experienced an issue: ", 5);
		std::cout << infoLog << std::endl << shaderSrc << std::endl;
		Error::crash("One or more shaders were unable to compile", 5);
	}
}

GLint ShaderProgram::getUniformLocation(std::string uniform) {
	GLint location = glGetUniformLocation(_shaderProgram, uniform.c_str());
	if (location == GL_INVALID_INDEX) {
		Error::crash("Could not find uniform in shader: " + uniform, 6);
	}
	return location;
}

void ShaderProgram::bindAttrib(std::string attribName) {
	//Error::log("Bound shader variable: " + attribName);
	glBindAttribLocation(_shaderProgram, _numAttribs++, attribName.c_str());
}

void ShaderProgram::use() {
	glUseProgram(_shaderProgram);
}

void ShaderProgram::unuse() {
	glUseProgram(0);
}