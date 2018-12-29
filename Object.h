#pragma once
#include <GL/glew.h>
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

	void rotate(const glm::vec3& delta);
	void move(float distance); 
	void addVelocity(float delta) { velocity += delta; }

	glm::mat4 getTransformMatrix() const;
	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScaling() const;

protected:
	float velocity;
	glm::vec3 positionVector;
	glm::vec3 rotationVector;
	glm::vec3 scalingVector;
	GLuint myVAO;
	GLuint myVBO;
	GLuint shaderArgMVP;
	GLuint myShader;
};

