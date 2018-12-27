#pragma once
#include "Object.h"
class Camera :
	public Object
{
public:
	Camera(int width, int height);
	~Camera();
	void Init();
	void Draw(const Camera& cam);
	void LookAt(glm::vec3 object);
	glm::mat4 Projection;
	glm::mat4 ViewMatrix;
	glm::mat4 getViewProjection() const;
};

