#pragma once

#include <string>
#include <map>
#include "Texture.h"
#include "ImageLoader.h"

class TextureCache
{
public:
	static Texture getTexture(std::string filePath);
private:
	static std::map<std::string, Texture> _textureMap;
};

