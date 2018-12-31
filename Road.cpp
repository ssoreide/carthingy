#include "Road.h"
#include "LoadShaders.h"
#include <math.h>
#include <iostream>
#include "TextureManager.h"
#include "Camera.h"
#include "Splines.h"
#include "Cube.h"
#include "Rectangle.h"
#include <glm/ext.hpp>

#define ROAD_IMAGE_ID 2

using namespace std;

float widthFactor = 0.7f;
float pi = (float)atan(1) * 4;
int texPerControlPoint = 5;
int segmentsPerTex = 10;

int arraySize;


Road::Road()
{
	myShader = LoadShaders("TextureVertexShader.glsl", "TextureFragmentShader.glsl");

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

	
	
	

	glGenVertexArrays(1, &myVAO);
	glBindVertexArray(myVAO);
	shaderArgMVP = glGetUniformLocation(myShader, "MVP");

	glGenBuffers(1, &myVBO);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glBufferData(GL_ARRAY_BUFFER, arraySize * sizeof(GLfloat), PosAndTexCoordinates, GL_STATIC_DRAW);

	TextureManager::Inst()->LoadTexture("textures\\road3.jpg", ROAD_IMAGE_ID);
	// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Generate mipmaps, by the way.
	glGenerateMipmap(GL_TEXTURE_2D);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // size, coordinates in position
		GL_FLOAT,           // type
		GL_FALSE,           // normalized? already between 1 and 0?
		5 * sizeof(float),  // stride nr of coordinates in bytes, distance between vertices
		(void*)0            // array buffer offset
	);
	glVertexAttribPointer(
		1,                  // attribute 1
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(float),  // stride
		(void*)(3 * sizeof(float))  // array buffer offset
	);
	glBindVertexArray(0);

	int number_of_gates = 20;
	for (int i = 0; i < number_of_gates; i++) {
		Object *gate = createGate();

		gate->setPosition(spline.getMidPoint((splinesegments * i / number_of_gates)));
		gate->setRotation(spline.getRotation((splinesegments * i / number_of_gates)));

		addChild(gate);
	}
}

Object* Road::createGate() {
	Cube *left = new Cube();
	Cube *right = new Cube();
	Cube *mid = new Cube();
	Square *sign = new Square();

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

void Road::Draw(const Camera& cam, const glm::mat4& transform) {
	glBindVertexArray(myVAO);
	glUseProgram(myShader);

	glm::mat4 projectionView = cam.getProjection() * glm::inverse(cam.getTransformMatrix());
	glm::mat4 mvp = projectionView * getTransformMatrix() * transform;

	glUniformMatrix4fv(shaderArgMVP, 1, GL_FALSE, &mvp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, arraySize / 5);
	glBindVertexArray(0);
	Object::Draw(cam, transform);
}