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
	virtual void Draw(const Camera& cam, const glm::mat4& transform);

	Object* createGate();
};

