#include "Road.h"
#include "LoadShaders.h"
#include <math.h>
#include <iostream>
#include "TextureManager.h"
#include "Camera.h"
#include "Splines.h"

#define ROAD_IMAGE_ID 2

using namespace std;

float widthFactor = 0.7f;
float pi = (float)atan(1) * 4;
int texPerControlPoint = 5;
int segmentsPerTex = 10;

int arraySize;


Road::Road()
{
}


Road::~Road()
{
}

void Road::Init() {
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

	arraySize = controlPoints.size() * segmentsPerTex * texPerControlPoint * 5 * 6;

	GLfloat * PosAndTexCoordinates = new GLfloat[arraySize];
	int p = 0;
	for (int i = 0; i < controlPoints.size() * texPerControlPoint; i++) {
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

}

void Road::Draw(const Camera& cam) {
	glBindVertexArray(myVAO);
	glUseProgram(myShader);

	glm::mat4 projectionView = cam.getProjection() * glm::inverse(cam.getTransformMatrix());
	glm::mat4 mvp = projectionView * getTransformMatrix();

	glUniformMatrix4fv(shaderArgMVP, 1, GL_FALSE, &mvp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, arraySize / 5);
	glBindVertexArray(0);
}