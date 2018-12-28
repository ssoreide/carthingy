#include "Object.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Object::Object()
{
	positionVector = glm::vec3(0.0);
	rotationVector = glm::vec3(0.0);
	scalingVector = glm::vec3(1.0);
}

Object::~Object()
{
}

void Object::setPosition(const glm::vec3& pos) {
	positionVector = pos;
}

void Object::setScaling(const glm::vec3& scale) {
	scalingVector = scale;
}

void Object::setRotation(const glm::vec3& rot) {
	rotationVector = rot;
}

void Object::rotate(const glm::vec3& delta) {
	rotationVector += delta;
}

void Object::move(float delta_time) {
	glm::vec3 direction = getTransformMatrix()*glm::vec4(0, 0, 1, 0);

	direction = glm::normalize(direction);
	positionVector += direction * velocity * delta_time;
}

glm::mat4 Object::getTransformMatrix() {
	glm::mat4 positionMatrix = glm::translate(glm::mat4(1), positionVector);
	glm::mat4 rotationMatrix = glm::toMat4(glm::quat(rotationVector));
	glm::mat4 scalingMatrix = glm::scale(scalingVector);
	return positionMatrix * rotationMatrix * scalingMatrix;
}
