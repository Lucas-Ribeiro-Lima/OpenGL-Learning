#define STB_IMAGE_IMPLEMENTATION

#include "Utils.h"
#include "stb_image.h"
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

	unsigned char* loadTexture(const char path[],	int& width, int& heigth, int& nrChannels) {
		stbi_set_flip_vertically_on_load(true);
		return stbi_load(path, &width, &heigth, &nrChannels, 0);
	}

	void freeTexture(unsigned char* data) {
		stbi_image_free(data);
	}
}