#pragma once
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture2D{
public:
	unsigned int ID;
	int width;
	int height;
	int nrChannels;

	Texture2D();
	Texture2D(const char* filename, bool isAlpha = false);

	void load(const char* filename);
	void setAlpha(bool setting);
	void setVerticalFlip(bool setting);
private:
	bool verticalFlip = false;
	bool alpha = false;
};

#endif