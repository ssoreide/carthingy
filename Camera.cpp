#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(int width, int height)
{
	projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
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


