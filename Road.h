#pragma once
#include "Object.h"
#include <GL/glew.h>

class Road :
	public Object
{
public:
	Road();
	~Road();

	virtual void Init();
	virtual void Draw(const glm::mat4& viewMatrix);

private:
	GLuint programID; // Shader program id
	GLuint vertexbuffer;
	GLuint MatrixID;
};

