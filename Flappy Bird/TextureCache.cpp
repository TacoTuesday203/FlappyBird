#include "TextureCache.h"

std::map<std::string, Texture> TextureCache::_textureMap;

Texture TextureCache::getTexture(std::string filePath) {
	auto mit = _textureMap.find(filePath);
	if (mit == _textureMap.end()) {
		Texture temp = ImageLoader::loadPNG(filePath);
		_textureMap.insert(make_pair(filePath, temp));
		//Error::log("New texture loaded.");
		return temp;
	}
	else {
		//Error::log("Cached texture loaded");
		return mit->second;
	}
}