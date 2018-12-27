#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(int width, int height)
{
	Projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
}

Camera::~Camera()
{
}

void Camera::Draw(const Camera& cam)
{
}

void Camera::Init()
{
}

void Camera::LookAt(glm::vec3 object) {
	ViewMatrix = glm::lookAt(
		positionVector,					// the position of your camera, in world space
		object,							// where you want to look at, in world space
		glm::vec3(0, 1, 0)				// up
	);
}

glm::mat4 Camera::getViewProjection() const{
	return Projection * ViewMatrix;
}


