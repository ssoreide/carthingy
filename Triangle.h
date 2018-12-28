#pragma once
#include "Object.h"
#include <GL/glew.h>

class Triangle :
	public Object
{
public:
	Triangle();
	~Triangle();

	virtual void Init();
	virtual void Draw(const glm::mat4& viewMatrix);

private:
	GLuint programID; // Shader program id
	GLuint myVBO;
	GLuint MatrixID;
	GLuint VertexArrayID;
};

