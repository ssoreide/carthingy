#pragma once
#include "Object.h"

class Camera : public Object
{
public:
	Camera(int width, int height);
	~Camera();
	void Init();
	void Draw(const Camera& cam); // Will probably not be used

	glm::mat4 getProjection() const { return projection;  }
private:
	glm::mat4 projection;
};

