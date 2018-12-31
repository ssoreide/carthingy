#pragma once
#include "Object.h"
#include <GL/glew.h>

class Road :
	public Object
{
public:
	Road();
	virtual void Draw(const Camera& cam, const glm::mat4& transform);

	Object* createGate();
};

