#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"
#include <glad/glad.h>

using namespace std;

Shader::Shader(const char* vtxPath, const char* fragPath) {
	int success;
	char infoLog[512];

	const char* vtxCode = readVertexShaderFile(vtxPath);
	const char* fragCode = readFragmentShaderFile(fragPath);

	unsigned int vtx = glCreateShader(GL_VERTEX_SHADER);
	unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vtx, 1, &vtxCode, NULL);
	glShaderSource(frag, 1, &fragCode, NULL);
	glCompileShader(vtx);
	glCompileShader(frag);

	glGetShaderiv(vtx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vtx, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << endl << infoLog << endl;
	}
	glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(frag, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << endl << infoLog << endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vtx);
	glAttachShader(ID, frag);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << endl << infoLog << endl;
	}

	glDeleteShader(vtx);
	glDeleteShader(frag);
	delete[] vtxCode;
	delete[] fragCode;
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const char* name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name), (int) value);
}

void Shader::setInt(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setFloat(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::setMat4(const char* name, glm::mat4 &mat) {
	unsigned int locate = glGetUniformLocation(ID, name);
	glUniformMatrix4fv(locate, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3(const char* name, float x, float y, float z) {
	unsigned int locate = glGetUniformLocation(ID, name);
	glUniform3f(locate, x, y, z);
}

void Shader::setVec3(const char* name, glm::vec3 vec) {
	unsigned int locate = glGetUniformLocation(ID, name);
	glUniform3f(locate, vec.x, vec.y, vec.z);
}

const char* Shader::readVertexShaderFile(const char* filename) {
	const char* output = readShaderFile(filename);
	if (output == NULL)
		cout << "ERROR::SHADER::VERTEX::UNABLE_TO_READ_SOURCE" << endl;
	return output;
}

const char* Shader::readFragmentShaderFile(const char* filename) {
	const char* output = readShaderFile(filename);
	if (output == NULL)
		cout << "ERROR::SHADER::FRAGMENT::UNABLE_TO_READ_SOURCE" << endl;
	return output;
}

const char* Shader::readShaderFile(const char* filename) {
	ifstream file;
	file.open(filename);
	char* output;
	if (file.is_open()) {
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		output = new char[length];
		for (int i = 0; i < length; i++) { // clear out mem leaks
			output[i] = NULL;
		}
		file.read(output, length);
	}
	else return NULL;
	cout << output << endl;
	file.close();
	return output;
}