#include "Road.h"
#include "LoadShaders.h"
#include <math.h>
#include <iostream>
#include "TextureManager.h"
#include "Camera.h"
#include "Splines.h"
#include "Cube.h"
#include "Square.h"
#include <glm/ext.hpp>

using namespace std;

float widthFactor = 0.7f;
float pi = (float)atan(1) * 4;
int texPerControlPoint = 5;
int segmentsPerTex = 10;

int arraySize;

Road::Road()
{
	std::vector<vec2> controlPoints;
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
	Spline spline(controlPoints, widthFactor, texPerControlPoint * segmentsPerTex);

	int splinesegments = controlPoints.size() * segmentsPerTex * texPerControlPoint;

	arraySize = splinesegments * 5 * 6;

	GLfloat * PosAndTexCoordinates = new GLfloat[arraySize];
	int p = 0;
	for (unsigned int i = 0; i < controlPoints.size() * texPerControlPoint; i++) {
		for (int j = 0; j < segmentsPerTex; j++) {
			int s = i * segmentsPerTex + j;
			int sn = (s + 1) % (arraySize / 30);

			//Triangle 1:
			//xyz
			PosAndTexCoordinates[p++] = spline.getOuterPoint(s)[0];
			PosAndTexCoordinates[p++] = 0.0f;
			PosAndTexCoordinates[p++] = spline.getOuterPoint(s)[1];
			//uv
			PosAndTexCoordinates[p++] = 0.0f;
			PosAndTexCoordinates[p++] = (float)j / segmentsPerTex;

			//xyz
			PosAndTexCoordinates[p++] = spline.getInnerPoint(s)[0];
			PosAndTexCoordinates[p++] = 0.0f;
			PosAndTexCoordinates[p++] = spline.getInnerPoint(s)[1];
			//uv
			PosAndTexCoordinates[p++] = 1.0f;
			PosAndTexCoordinates[p++] = (float)j / segmentsPerTex;

			//xyz
			PosAndTexCoordinates[p++] = spline.getInnerPoint(sn)[0];
			PosAndTexCoordinates[p++] = 0.0f;
			PosAndTexCoordinates[p++] = spline.getInnerPoint(sn)[1];
			//uv
			PosAndTexCoordinates[p++] = 1.0f;
			PosAndTexCoordinates[p++] = (float)(j + 1) / segmentsPerTex;


			//Triangle 2:
			//xyz
			PosAndTexCoordinates[p++] = spline.getOuterPoint(sn)[0];
			PosAndTexCoordinates[p++] = 0.0f;
			PosAndTexCoordinates[p++] = spline.getOuterPoint(sn)[1];
			//uv
			PosAndTexCoordinates[p++] = 0.0f;
			PosAndTexCoordinates[p++] = (float)(j + 1) / segmentsPerTex;

			//xyz
			PosAndTexCoordinates[p++] = spline.getInnerPoint(sn)[0];
			PosAndTexCoordinates[p++] = 0.0f;
			PosAndTexCoordinates[p++] = spline.getInnerPoint(sn)[1];
			//uv
			PosAndTexCoordinates[p++] = 1.0f;
			PosAndTexCoordinates[p++] = (float)(j + 1) / segmentsPerTex;

			//xyz
			PosAndTexCoordinates[p++] = spline.getOuterPoint(s)[0];
			PosAndTexCoordinates[p++] = 0.0f;
			PosAndTexCoordinates[p++] = spline.getOuterPoint(s)[1];
			//uv
			PosAndTexCoordinates[p++] = 0.0f;
			PosAndTexCoordinates[p++] = (float)j / segmentsPerTex;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glBufferData(GL_ARRAY_BUFFER, arraySize * sizeof(GLfloat), PosAndTexCoordinates, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // size, coordinates in position
		GL_FLOAT,           // type
		GL_FALSE,           // normalized? already between 1 and 0?
		5 * sizeof(float),  // stride nr of coordinates in bytes, distance between vertices
		(void*)0            // array buffer offset
	);
	glVertexAttribPointer(
		2,                  // attribute 1
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(float),  // stride
		(void*)(3 * sizeof(float))  // array buffer offset
	);
	setTexture("textures\\road3.jpg");

	int number_of_gates = 20;
	for (int i = 0; i < number_of_gates; i++) {
		Object *gate = createGate();

		gate->setPosition(spline.getMidPoint((splinesegments * i / number_of_gates)));
		gate->setRotation(spline.getRotation((splinesegments * i / number_of_gates)));

		addChild(gate);
	}
}

void Road::Draw(const Camera& cam, const glm::mat4& transform) {
	Object::Draw(cam, transform);
	glDrawArrays(GL_TRIANGLES, 0, arraySize / 5);
}

Object* Road::createGate() {
	Cube *left = new Cube();
	Cube *right = new Cube();
	Cube *mid = new Cube();
	Square *sign = new Square();
	sign->setTexture("textures\\bacon.jpg");

	left->setPosition(glm::vec3(-1, 1.5, 0));
	left->setScaling(glm::vec3(0.1, 3, 0.1));

	right->setPosition(glm::vec3(1, 1.5, 0));
	right->setScaling(glm::vec3(0.1, 3, 0.1));

	mid->setPosition(glm::vec3(0, 1, 0));
	mid->setScaling(glm::vec3(2, 1, 0.1));

	sign->setPosition(glm::vec3(0, 1, 0.2f));
	sign->setScaling(glm::vec3(1.0, 0.5, 0.1));

	Object *gate = new Object();
	gate->addChild(left);
	gate->addChild(right);
	gate->addChild(mid);
	gate->addChild(sign);

	return gate;
}
