#pragma once
#include "Object.h"

class Camera : public Object
{
public:
	Camera(int width, int height);
	~Camera();
	void Init();
	void Draw(const glm::mat4& viewMatrix); // Will probably not be used

	glm::mat4 getProjection() { return projection;  }
private:
	glm::mat4 projection;
};

