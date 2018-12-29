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
	GLuint normalbuffer;
};

