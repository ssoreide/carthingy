#pragma once
#include "Object.h"
#include <GL/glew.h>

class Cube : public Object
{
public:
	Cube();
	virtual void Draw(const Camera& cam, const glm::mat4& transform);
};

