#include "Splines.h"

Spline::Spline(std::vector<vec2> controlPoints, float width, int pointsPerSegment) {
	std::vector<vec2> pointsOnCurve;
	for (int i = 0; i < controlPoints.size(); i++) {
		vec2 p0 = controlPoints[i];
		vec2 p1 = controlPoints[(i + 1) % controlPoints.size()];
		vec2 p2 = controlPoints[(i + 2) % controlPoints.size()];
		vec2 p3 = controlPoints[(i + 3) % controlPoints.size()];
		for (int j = 0; j < pointsPerSegment; j++) {
			pointsOnCurve.push_back(catmullRom(p0, p1, p2, p3, (float)j / pointsPerSegment));
		}
	}
	for (int i = 0; i < pointsOnCurve.size(); i++) {
		vec2 p0 = pointsOnCurve[i];
		vec2 p1 = pointsOnCurve[(i + 1) % pointsOnCurve.size()];
		vec2 delta = p1 - p0;
		//towards center of closed curve going counter-clockwise
		vec2 normalVector = vec2(-delta[1], delta[0]);
		innerPoints.push_back(p0 + width * normalVector);
		outerPoints.push_back(p0 - width * normalVector);
	}
}

vec2 Spline::getInnerPoint(unsigned int index) {
	return innerPoints[index];
}

vec2 Spline::getOuterPoint(unsigned int index) {
	return outerPoints[index];
}