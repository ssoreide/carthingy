#include "Road.h"
#include <math.h>
#include <iostream>
#include "TextureManager.h"
#include "Splines.h"
#include "Cube.h"
#include "Square.h"
#include <glm/ext.hpp>

using namespace std;
using namespace glm;

float widthFactor = 0.7f;
float pi = (float)atan(1) * 4;
int texPerControlPoint = 5;
int segmentsPerTex = 10;

int arraySize;

Road::Road()
{
	controlPoints.push_back(10.0f * vec2(0.0, 0.0));
	controlPoints.push_back(10.0f * vec2(1.0, 0.0));
	controlPoints.push_back(10.0f * vec2(2.0, 0.0));
	controlPoints.push_back(10.0f * vec2(3.0, 0.0));
	controlPoints.push_back(10.0f * vec2(4.0, 1.0));
	controlPoints.push_back(10.0f * vec2(3.0, 2.0));
	controlPoints.push_back(10.0f * vec2(2.0, 2.0));
	controlPoints.push_back(10.0f * vec2(2.0, 3.0));
	controlPoints.push_back(10.0f * vec2(1.0, 4.0));
	controlPoints.push_back(10.0f * vec2(0.0, 3.0));
	controlPoints.push_back(10.0f * vec2(0.0, 2.0));
	controlPoints.push_back(10.0f * vec2(0.0, 1.0));
	spline = new Spline(controlPoints, widthFactor, texPerControlPoint * segmentsPerTex);

	int splinesegments = controlPoints.size() * segmentsPerTex * texPerControlPoint;
	int number_of_gates = 20;
	for (int i = 0; i < number_of_gates; i++) {
		Object *gate = createGate();

		gate->setPosition(spline->getMidPoint((splinesegments * i / number_of_gates)));
		gate->setRotation(spline->getRotation((splinesegments * i / number_of_gates)));

		addChild(gate);
	}
}

vector<glm::vec3> Road::getTrackLights() {
	int splinesegments = controlPoints.size() * segmentsPerTex * texPerControlPoint;
	vector<glm::vec3> result;
	for (int i = 0; i < 4; i++) {
		glm::vec3 p = spline->getMidPoint((splinesegments * i / 4));
		p += glm::vec3(0, 2, 0);
		result.push_back(p);
	}
	return result;
}

void Road::Draw() {
	DrawChildren();
	UpdateMaterial();

	setTexture("textures\\road3.jpg");
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(getTransformMatrix()));

	if (myTexture != "") {
		TextureManager::Inst()->BindTexture(myTexture);
	}


	int splinesegments = controlPoints.size() * segmentsPerTex * texPerControlPoint;
	// 8 = antall komponenter per vertex (x, y, z, u, v, xNormal, yNormal, zNormal)
	// 6 = to triangler per segment, som blir 6 vertices
	arraySize = splinesegments * 8 * 6;

	int p = 0;
	for (unsigned int i = 0; i < controlPoints.size() * texPerControlPoint; i++) {
		for (int j = 0; j < segmentsPerTex; j++) {
			int s = i * segmentsPerTex + j;
			int sn = (s + 1) % (arraySize / (8 * 6));

			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
			glTexCoord2d(0.0f, (float)j / segmentsPerTex); glVertex3f(spline->getInnerPoint(s)[0], 0, spline->getInnerPoint(s)[1]);
			glTexCoord2d(0.0f, (float)(j + 1) / segmentsPerTex); glVertex3f(spline->getInnerPoint(sn)[0], 0, spline->getInnerPoint(sn)[1]);
			glTexCoord2d(1.0f, (float)(j + 1) / segmentsPerTex); glVertex3f(spline->getOuterPoint(sn)[0], 0, spline->getOuterPoint(sn)[1]);
			glTexCoord2d(1.0f, (float)j / segmentsPerTex); glVertex3f(spline->getOuterPoint(s)[0], 0, spline->getOuterPoint(s)[1]);
			glEnd();
		}
	}

	glPopMatrix();

}

Object* Road::createGate() {
	Cube *left = new Cube();
	Cube *right = new Cube();
	Cube *mid = new Cube();
	Square *sign1 = new Square();
	sign1->setTexture("textures\\bacon.jpg");
	Square *sign2 = new Square();
	sign2->setTexture("textures\\bacon.jpg");

	left->setColor(glm::vec3(1, 0, 1));
	left->setPosition(glm::vec3(-1, 1.5, 0));
	left->setScaling(glm::vec3(0.1, 3, 0.1));

	right->setPosition(glm::vec3(1, 1.5, 0));
	right->setScaling(glm::vec3(0.1, 3, 0.1));

	mid->setPosition(glm::vec3(0, 1, 0));
	mid->setScaling(glm::vec3(2, 1, 0.1));

	sign1->setPosition(glm::vec3(0, 1, 0.2f));
	sign1->setScaling(glm::vec3(1.0, 0.5, 0.1));

	sign2->setPosition(glm::vec3(0, 1, -0.2f));
	sign2->setScaling(glm::vec3(1.0, 0.5, 0.1));
	sign2->setRotation(glm::vec3(0, 3.14159, 0));

	Object *gate = new Object();
	gate->addChild(left);
	gate->addChild(right);
	gate->addChild(mid);
	gate->addChild(sign1);
	gate->addChild(sign2);

	cout << "Created gate...\n";

	return gate;
}
