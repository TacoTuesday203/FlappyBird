#include "IOManager.h"

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& in) {
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		return false;
	}
	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	fileSize -= file.tellg();

	in.resize(fileSize);
	file.read((char*)&(in[0]), fileSize);
	file.close();

	return true;
}