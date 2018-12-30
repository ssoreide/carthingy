#pragma once
#include "Object.h"

class Camera : public Object
{
public:
	Camera(int width, int height);
	~Camera();
	void Init();
	void Draw(const Camera& cam, const glm::mat4& transform);

	glm::mat4 getProjection() const { return projection;  }
private:
	glm::mat4 projection;
};

