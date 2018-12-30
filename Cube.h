#pragma once
#include "Object.h"
#include <GL/glew.h>

class Cube : public Object
{
public:
	Cube();
	~Cube();

	virtual void Init();
	virtual void Draw(const Camera& cam, const glm::mat4& transform);
private:
	GLuint shaderArgLightPos;
	GLuint shaderArgProjection;
	GLuint shaderArgModel;
	GLuint shaderArgView;
};

