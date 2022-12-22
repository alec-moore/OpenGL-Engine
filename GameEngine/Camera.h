#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	Camera(
		glm::vec3 positionTemp = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 upTemp = glm::vec3(0.0f, 1.0f, 0.0f),
		float yawNew = YAW,
		float pitchNew = PITCH
	) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
		movementSpeed(SPEED),
		mouseSensitivity(SENSITIVITY),
		zoom(ZOOM) 
	{
		position = positionTemp;
		worldUp = upTemp;
		yaw = yawNew;
		pitch = pitchNew;
		updateCameraVectors();
	}

	Camera(
		float posX,
		float posY,
		float posZ,
		float upX,
		float upY,
		float upZ,
		float yawNew = YAW,
		float pitchNew = PITCH
	) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
		movementSpeed(SPEED),
		mouseSensitivity(SENSITIVITY),
		zoom(ZOOM)
	{
		position = glm::vec3(posX, posY, posZ);
		worldUp = glm::vec3(upX, upY, upZ);
		yaw = yawNew;
		pitch = pitchNew;

		updateCameraVectors();
	}

	glm::mat4 getViewMatrix() {
		return glm::lookAt(position, position + front, up);
	}

	void processKeyboard(Camera_Movement direction, float deltaTime) {
		float vel = movementSpeed * deltaTime;
		switch (direction) {
			case FORWARD:
				position += front * vel;
				break;
			case BACKWARD:
				position -= front * vel;
				break;
			case LEFT:
				position -= right * vel;
				break;
			case RIGHT:
				position += right * vel;
				break;
			case UP:
				position += up * vel;
				break;
			case DOWN:
				position -= up * vel;
				break;
		}
	}

	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;
		
		yaw += xoffset;
		pitch += yoffset;

		if (constrainPitch) {
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void processMouseScroll(float yoffset) {
		zoom -= (float)yoffset;
		if (zoom < 1.0f)
			zoom = 1.0f;
		if (zoom > 45.0f)
			zoom = 45.0f;
	}

private:
	void updateCameraVectors() {
		glm::vec3 frontNew;
		frontNew.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		frontNew.y = sin(glm::radians(pitch));
		frontNew.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		
		front = glm::normalize(frontNew);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
};


#endif