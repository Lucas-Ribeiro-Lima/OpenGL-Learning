#include "Texture.h"

//Map for the colors system of images of stb_images
const int colorSystem[4] = { GL_RED, NULL, GL_RGB, GL_RGBA };

Texture::Texture(const char* path) {
	int width, heigth, nrChannels;
	unsigned char* data = Utils::loadTexture(path, width, heigth, nrChannels, true);

	glGenTextures(1, &TEX);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TEX);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, colorSystem[nrChannels - 1], width, heigth, 0, colorSystem[nrChannels - 1], GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	Utils::freeTexture(data);
}

GLuint Texture::getTex() const {
	return TEX;
}