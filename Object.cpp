#include "Object.h"
#include "TextureManager.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Object::Object()
{
	positionVector = glm::vec3(0.0);
	rotationVector = glm::vec3(0.0);
	scalingVector = glm::vec3(1.0);
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

void Object::setTexture(const std::string textureFileName) {
	TextureManager::Inst()->LoadTexture(textureFileName);
	myTexture = textureFileName;
}


void Object::Draw(const Camera& cam, const glm::mat4& transform) {
	glm::mat4 t = transform * getTransformMatrix();
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->Draw(cam, t);
	}
}

void Object::addChild(Object* obj) {
	children.push_back(obj);
}

void Object::move(float delta_time) {
	glm::vec3 direction = getTransformMatrix()*glm::vec4(0, 0, 1, 0);

	direction = glm::normalize(direction);
	positionVector += direction * velocity * delta_time;
}

glm::mat4 Object::getTransformMatrix() const {
	glm::mat4 positionMatrix = glm::translate(glm::mat4(1), positionVector);
	glm::mat4 rotationMatrix = glm::toMat4(glm::quat(rotationVector));
	glm::mat4 scalingMatrix = glm::scale(scalingVector);
	return positionMatrix * rotationMatrix * scalingMatrix;
}

glm::vec3 Object::getPosition() const {
	return positionVector;
}

glm::vec3 Object::getRotation() const {
	return rotationVector;
}

glm::vec3 Object::getScaling() const {
	return scalingVector;
}
