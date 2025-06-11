#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Utils.h"

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

	void writeFile(const char* path, auto content) {
		try {
			std::ofstream file(path);

			file.exceptions(file.failbit | file.badbit);

			file << content << std::endl;

			file.close();
		}
		catch(const std::ofstream::failure& e) {

			throw std::runtime_error(e.what());

		}
	}

	void logger(const char* log) {
		time_t timestamp = time(NULL);
		struct tm datetime;

		#ifdef _WIN32
				localtime_s(&datetime, &timestamp);
		#else
				localtime_r(&timestamp, &datetime);
		#endif

		char ascDateTime[26];
		asctime_s(ascDateTime, &datetime);

		std::string formattedStr = std::format("Date: {} - {}", ascDateTime, log);

		writeFile("log.txt", formattedStr);
	}

	void genPlanetsOrbit(std::vector<glm::vec3>& positions) {
		for (int i = 0; i < Constants::DISTANCES_PLANETS.size(); i++) {
			float angle = glm::radians(i * 360.0f / Constants::DISTANCES_PLANETS.size());
			float x = cos(angle) * Constants::DISTANCES_PLANETS[i];
			float z = sin(angle) * Constants::DISTANCES_PLANETS[i];
			positions.push_back(glm::vec3(x, 0.0f, z));
		}
	}

	unsigned char* loadTexture(const char path[],	int& width, int& heigth, int& nrChannels, bool flip) {
		stbi_set_flip_vertically_on_load(flip);
		return stbi_load(path, &width, &heigth, &nrChannels, 0);
	}

	void freeTexture(unsigned char* data) {
		stbi_image_free(data);
	}
}