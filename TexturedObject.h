#pragma once
#include "Object.h"
#include <GL/glew.h>

class TexturedObject : public Object
{
public:
	TexturedObject();
	~TexturedObject();

	virtual void Init();
	virtual void Draw(const Camera& cam);
};

