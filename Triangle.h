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
	virtual void Draw(const Camera& cam, const glm::mat4& transform);
};

