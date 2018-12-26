#pragma once
#include <glm/gtc/matrix_transform.hpp>

class Object
{
public:
	Object();
	~Object();

	virtual void Init() = 0;
	virtual void Draw(const glm::mat4& viewMatrix) = 0;

	void setPosition(const glm::vec3& pos);
	void setRotation(const glm::vec3& rotation);
	void setScaling(const glm::vec3& scale);

	glm::mat4 getTransformMatrix();

protected:
	glm::mat4 positionMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scalingMatrix;

};

