#pragma once

#include <iostream>
#include <conio.h>
#include <string>

namespace Error {
	extern void log(std::string msg);
	extern void error(std::string msg, int code);
	extern void crash(std::string msg, int code);
}