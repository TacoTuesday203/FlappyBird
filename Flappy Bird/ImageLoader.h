#pragma once

#include <vector>
#include "Texture.h"
#include "IOManager.h"
#include "Error.h"
#include "picoPNG.h"

class ImageLoader
{
public:
	static Texture loadPNG(std::string filePath);
};

