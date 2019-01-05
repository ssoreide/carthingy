#pragma once
#include "Object.h"

class Camera : public Object
{
public:
	Camera(int width, int height);
	void Draw();

	glm::mat4 getProjection() const { return projection; }
private:
	glm::mat4 projection;
};

