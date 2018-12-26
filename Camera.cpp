#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Draw(const glm::mat4& viewMatrix)
{
}

void Camera::Init()
{
}

void Camera::LookAt(glm::vec3 object) {
	glm::mat4 CameraMatrix = glm::lookAt(
		glm::vec3(positionMatrix[3]),	// the position of your camera, in world space
		object,							// where you want to look at, in world space
		glm::vec3(0, 1, 0)				// up
	);
}

