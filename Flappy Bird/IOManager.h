#pragma once

#include <fstream>
#include <vector>
#include <string>

class IOManager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& in);
};

