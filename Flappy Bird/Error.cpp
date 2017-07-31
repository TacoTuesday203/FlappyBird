#include "Error.h"

namespace Error {
	void log(std::string msg) {
		std::cout << "[LOG] " << msg << std::endl;
	}

	void error(std::string msg, int code) {
		std::cout << "[ERROR] " << msg << " (" << code << ")" << std::endl;
		_getch();
	}

	void crash(std::string msg, int code) {
		std::cout << "[CRASH] " << msg << " (" << code << ")" << std::endl;
		_getch();
		exit(code);
	}
}