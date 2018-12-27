#pragma once
#include <glm/gtc/matrix_transform.hpp>

class Camera;

class Object
{
public:
	Object();
	~Object();

	virtual void Init() = 0;
	virtual void Draw(const Camera& cam) = 0;

	void setPosition(const glm::vec3& pos);
	void setRotation(const glm::vec3& rotation);
	void setScaling(const glm::vec3& scale);

	glm::mat4 getTransformMatrix();
	glm::vec3 getPosition() const;
	glm::vec3 getRotation();
	glm::vec3 getScaling();

protected:
	glm::vec3 positionVector;
	glm::vec3 rotationVector;
	glm::vec3 scalingVector;
};

