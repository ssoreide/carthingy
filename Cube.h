#pragma once
#include "Object.h"
#include <GL/glew.h>

class Cube : public Object
{
public:
	Cube();
	~Cube();

	virtual void Init();
	virtual void Draw(const glm::mat4& viewMatrix);
private:
	GLuint programID; // Shader program id
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint MatrixID;
};

