#pragma once
#include "Object.h"
class Camera :
	public Object
{
public:
	Camera();
	~Camera();
	void Init();
	void Draw(const glm::mat4& viewMatrix);
	void LookAt(glm::vec3 object);
};

