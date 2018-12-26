#include "Object.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Object::Object()
{
	positionMatrix = glm::mat4(1);
	scalingMatrix = glm::mat4(1);
	rotationMatrix = glm::mat4(1);
}


Object::~Object()
{
}

void Object::setPosition(const glm::vec3& pos) {
	positionMatrix = glm::translate(glm::mat4(1), pos);
}

void Object::setScaling(const glm::vec3& scale) {
	scalingMatrix = glm::scale(scale);
}

void Object::setRotation(const glm::vec3& rot) {
	rotationMatrix = glm::toMat4(glm::quat(rot));
}

glm::mat4 Object::getTransformMatrix() {
	return positionMatrix * rotationMatrix * scalingMatrix;
}
