#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vtxPath, const char* fragPath);
	void use();
	void setBool(const char* name, bool value) const;
	void setInt(const char* name, int value) const;
	void setFloat(const char* name, float value) const;
	void setMat4(const char* name, glm::mat4& mat);
	void setVec3(const char* name, float x, float y, float z);
	void setVec3(const char* name, glm::vec3);

private:
	const char* readFragmentShaderFile(const char* filename);
	const char* readVertexShaderFile(const char* filename);
	const char* readShaderFile(const char* filename);
};



#endif