#include "ImageLoader.h"

Texture ImageLoader::loadPNG(std::string filePath) {
	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	Texture text = {};

	unsigned long width, height;

	if (!IOManager::readFileToBuffer(filePath, in)) {
		Error::error("Unable to load texture: " + filePath, 7);
		return{};
	}

	int errCode = decodePNG(out, width, height, &in[0], in.size(), true);
	if (errCode != 0) {
		Error::error("Unable to decode PNG: " + filePath, 8);
		return{};
	}

	glGenTextures(1, &text.textureID);

	glBindTexture(GL_TEXTURE_2D, text.textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glGenerateMipmap(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	text.width = width;
	text.height = height;

	return text;
}