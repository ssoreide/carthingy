#pragma once
#include "Object.h"
#include <GL/glew.h>

class Square :
	public Object
{
public:
	Square();
	virtual void Draw(const Camera& cam, const glm::mat4& transform);
};

