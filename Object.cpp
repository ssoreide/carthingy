#include "Object.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Object::Object()
{
	positionVector = glm::vec3();
	rotationVector = glm::vec3();
	scalingVector = glm::vec3();
}


Object::~Object()
{
}

void Object::setPosition(const glm::vec3& pos) {
	//positionMatrix = glm::translate(glm::mat4(1), pos);
	positionVector = pos;
}

void Object::setScaling(const glm::vec3& scale) {
	//scalingMatrix = glm::scale(scale);
	scalingVector = scale;
}

void Object::setRotation(const glm::vec3& rot) {
	//rotationMatrix = glm::toMat4(glm::quat(rot));
	rotationVector = rot;
}

glm::mat4 Object::getTransformMatrix() {
	glm::mat4 positionMatrix = glm::translate(glm::mat4(1), positionVector);
	glm::mat4 rotationMatrix = glm::toMat4(glm::quat(rotationVector));
	glm::mat4 scalingMatrix = glm::scale(scalingVector);
	return positionMatrix * rotationMatrix * scalingMatrix;
}

glm::vec3 Object::getPosition() const{
	return positionVector;
}