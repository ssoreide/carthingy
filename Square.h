#pragma once
#include "Object.h"
#include <GL/glew.h>

class Square :
	public Object
{
public:
	Square(const std::string& texture);
	virtual void Draw(const Camera& cam, const glm::mat4& transform);
};

