#pragma once
#include "Object.h"

class Spline;

class Road : public Object
{
public:
	Road();
	virtual void Draw();
	vector<glm::vec3> getTrackLights();

private:
	Spline *spline;
	Object* createGate();
	std::vector<glm::vec2> controlPoints;
};

