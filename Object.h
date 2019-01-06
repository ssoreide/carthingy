#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

using namespace std;

class Object
{
public:
	Object();

	virtual void Draw();
	void DrawChildren();
	void UpdateMaterial();

	void setPosition(const glm::vec3& pos);
	void setRotation(const glm::vec3& rotation);
	void setScaling(const glm::vec3& scale);

	// hvis jeg ikke bruker setTexture, bruk setColor
	void setTexture(const std::string textureFileName);
	void setColor(const glm::vec3 color) { colorVector = color; }

	void rotate(const glm::vec3& delta);
	void move(float distance);
	void addVelocity(float delta) 
	{ 
		velocity += delta;
		if (velocity > 0) {
			velocity = 0;
		}
	}

	void addChild(Object* obj);

	glm::mat4 getTransformMatrix() const;
	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScaling() const;
	float getVelocity();

protected:
	vector<Object*> children;
	float velocity;
	glm::vec3 rotationVelocity;

	glm::vec3 positionVector;
	glm::vec3 rotationVector;
	glm::vec3 scalingVector;
	glm::vec3 colorVector;
	glm::vec3 lightPositionVector;

	std::string myTexture;
};

