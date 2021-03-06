#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/spline.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace glm;

class Spline {
public:
	Spline(std::vector<vec2> controlPoints, float width, int n);
	vec2 getInnerPoint(unsigned int index);
	vec2 getOuterPoint(unsigned int index);
	vec3 getRotation(unsigned int index);
	vec3 getMidPoint(unsigned int index);
private:
	std::vector<vec2> innerPoints;
	std::vector<vec2> outerPoints;
};