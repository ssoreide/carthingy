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
	virtual void Draw(const Camera& cam);

private:
	GLuint programID; // Shader program id
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint MatrixID;
	GLuint cameraPosID;
};

