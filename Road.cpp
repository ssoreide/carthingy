#include "Road.h"
#include "LoadShaders.h"
#include <math.h>
#include <iostream>
#include "TextureManager.h"
#include "Camera.h"

#define ROAD_IMAGE_ID 2

using namespace std;

/*static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, 0, 0.5f,
	1.0f, 0, 0.5f,
	0.3f,  0, 0.0f,
};*/

int textureSegments = 30;
int sectorsPerTextureSegments = 10;
int totalSegments = textureSegments * sectorsPerTextureSegments;

Road::Road()
{
}


Road::~Road()
{
}

void Road::Init() {
	myShader = LoadShaders("TextureVertexShader.glsl", "TextureFragmentShader.glsl");
	float widthFactor = 0.7f;
	float pi = (float)atan(1) * 4;
	int vps = 6; //vertices per segment
	int cps = 5 * vps; //components per segment
	int arraySize = textureSegments * sectorsPerTextureSegments * cps;

	GLfloat *PosAndTexCoordinates = new GLfloat[arraySize];
	int p = 0;
	for (int ts = 0; ts < textureSegments; ts++) {
		double sectorOffset = (2 * pi / textureSegments) * ts;

		for (int i = 0; i < sectorsPerTextureSegments; i++) {
			float startAngle = (float)(i * 2 * pi / totalSegments) + sectorOffset;
			float endAngle = (float)((i + 1) * 2 * pi / totalSegments) + sectorOffset;
			
			// TRIANGLE 1
			PosAndTexCoordinates[p++] = cos(startAngle);
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(startAngle);
			PosAndTexCoordinates[p++] = 1.0;
			PosAndTexCoordinates[p++] = (float)i / sectorsPerTextureSegments;

			PosAndTexCoordinates[p++] = cos(startAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(startAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = (float)i / sectorsPerTextureSegments;

			PosAndTexCoordinates[p++] = cos(endAngle);
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(endAngle);
			PosAndTexCoordinates[p++] = 1;
			PosAndTexCoordinates[p++] = (float)(i + 1) / sectorsPerTextureSegments;

			// TRIANGLE 2
			PosAndTexCoordinates[p++] = cos(startAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(startAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = (float)i / sectorsPerTextureSegments;

			PosAndTexCoordinates[p++] = cos(endAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(endAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = (float)(i + 1) / sectorsPerTextureSegments;

			PosAndTexCoordinates[p++] = cos(endAngle);
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(endAngle);
			PosAndTexCoordinates[p++] = 1;
			PosAndTexCoordinates[p++] = (float)(i + 1) / sectorsPerTextureSegments;
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
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//	TextureManager::Inst()->BindTexture(ROAD_IMAGE_ID);

	glm::mat4 mvp = cam.getTransformMatrix() * getTransformMatrix();
	glUniformMatrix4fv(shaderArgMVP, 1, GL_FALSE, &mvp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, textureSegments * sectorsPerTextureSegments * 6);
	glBindVertexArray(0);
}