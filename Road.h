#pragma once
#include "Object.h"

class Spline;

class Road : public Object
{
public:
	Road();
	virtual void Draw();
	vector<glm::vec3> getTrackLights();
	void takeOffTexture(bool tex) {
		if (tex) {
			textureRoad = "textures\\road3.jpg"; textureSign = "textures\\cola.jpg";
		}
		else { textureRoad = ""; textureSign = ""; }
	};

private:
	Spline *spline;
	Object* createGate();
	std::vector<glm::vec2> controlPoints;
	string textureRoad = "textures\\road.jpg";
	string textureSign = "textures\\cola.jpg"
};

