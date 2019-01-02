#pragma once
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

using namespace std;

class Camera;

class Object
{
public:
	Object();

	virtual void Draw(const Camera& cam, const glm::mat4& transform);

	void setPosition(const glm::vec3& pos);
	void setRotation(const glm::vec3& rotation);
	void setScaling(const glm::vec3& scale);

	void setTexture(const std::string textureFileName);
	void setColor(const glm::vec3 color) { colorVector = color; }
	void setLightPosition(const glm::vec3 lightPosition) { lightPositionVector = lightPosition; }

	void rotate(const glm::vec3& delta);
	void move(float distance); 
	void addVelocity(float delta) { velocity += delta; }

	void addChild(Object* obj);
	
	glm::mat4 getTransformMatrix() const;
	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScaling() const;

protected:
	vector<Object*> children;
	float velocity;
	glm::vec3 positionVector;
	glm::vec3 rotationVector;
	glm::vec3 scalingVector;
	glm::vec3 colorVector;
	glm::vec3 lightPositionVector;
	GLuint useTexture;

	GLuint myVAO;
	GLuint myVBO;
	GLuint shaderArgMVP;
	GLuint myShader;
	std::string myTexture;
	GLuint shaderArgLightPos;
	GLuint shaderArgProjection;
	GLuint shaderArgModel;
	GLuint shaderArgView;
	GLuint shaderArgUseTexture;
	GLuint shaderArgObjectColor;
};

