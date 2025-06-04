#include "Utils.h"
#include <fstream>
#include <sstream>

namespace Utils {
	std::string readFile(const char shaderName[]) {
		try {
			std::ifstream file(shaderName);
			
			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			
			std::stringstream buffer;

			buffer << file.rdbuf();

			return buffer.str();
		}
		catch(const std::ifstream::failure& e) {

			throw std::runtime_error(e.what());

		}
	}
}