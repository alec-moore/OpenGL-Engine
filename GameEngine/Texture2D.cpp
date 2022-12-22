#include <stdafx.h>
#include <Texture2D.h>
#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Texture2D::Texture2D(){

}

Texture2D::Texture2D(const char* filename, bool isAlpha){
	alpha = isAlpha;

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	stbi_set_flip_vertically_on_load(verticalFlip);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data) {
		if(alpha) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Image loaded!" << std::endl;
	}
	else {
		std::cout << "Failed to load 2D texture..." << std::endl;
	}

	stbi_image_free(data);
}

void Texture2D::load(const char* filename) {
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	stbi_set_flip_vertically_on_load(verticalFlip);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data) {
		if (alpha) 
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else 
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load 2D texture..." << std::endl;
	}

	stbi_image_free(data);
}

void Texture2D::setAlpha(bool setting) {
	alpha = setting;
}

void Texture2D::setVerticalFlip(bool setting) {
	verticalFlip = setting;
}