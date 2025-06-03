#include "Utils.h"
#include <streambuf>
#include <fstream>
#include <sstream>

namespace Utils {
	std::string readShader(const char* shaderName) {
		std::ifstream file(shaderName);

		if (!file) throw std::runtime_error("Error loading shader ");

		std::stringstream buffer;

		buffer << file.rdbuf();

		return buffer.str();
	}
}