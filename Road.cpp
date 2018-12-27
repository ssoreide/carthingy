#include "Road.h"
#include "LoadShaders.h"
#include <math.h>
#include <iostream>
#include "TextureManager.h"

#define ROAD_IMAGE_ID 2

using namespace std;

/*static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, 0, 0.5f,
	1.0f, 0, 0.5f,
	0.3f,  0, 0.0f,
};*/

int numberSegments = 100;
int textureSegments = 10;
int sectorsPerTextureSegments = 10;

Road::Road()
{
}


Road::~Road()
{
}

void Road::Init() {
	programID = LoadShaders("TextureVertexShader.glsl", "TextureFragmentShader.glsl");
	std::cout << "Road programID: " << programID << "\n";

	int n = numberSegments;
	float widthFactor = 0.8;
	float pi = atan(1) * 4;
	int vps = 6; //vertices per segment
	int cps = 5 * vps; //components per segment
	int arraySize = textureSegments * sectorsPerTextureSegments * cps;

	GLfloat *PosAndTexCoordinates = new GLfloat[arraySize];
	int p = 0;
	for (int ts = 0; ts < textureSegments; ts++) {
		double sectorOffset = (2 * pi / textureSegments) * ts;

		for (int i = 0; i < sectorsPerTextureSegments; i++) {
			float startAngle = (i * 2 * pi / n) + sectorOffset;
			float endAngle = ((i + 1) * 2 * pi / n) + sectorOffset;
			
			// TRIANGLE 1
			PosAndTexCoordinates[p++] = cos(startAngle);
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(startAngle);
			PosAndTexCoordinates[p++] = 1.0;
			PosAndTexCoordinates[p++] = i / sectorsPerTextureSegments;

			PosAndTexCoordinates[p++] = cos(startAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(startAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = i / sectorsPerTextureSegments;

			PosAndTexCoordinates[p++] = cos(endAngle);
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(endAngle);
			PosAndTexCoordinates[p++] = 1;
			PosAndTexCoordinates[p++] = (i + 1) / sectorsPerTextureSegments;

			// TRIANGLE 2
			PosAndTexCoordinates[p++] = cos(startAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(startAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = i / sectorsPerTextureSegments;

			PosAndTexCoordinates[p++] = cos(endAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(endAngle) * widthFactor;
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = (i + 1) / sectorsPerTextureSegments;

			PosAndTexCoordinates[p++] = cos(endAngle);
			PosAndTexCoordinates[p++] = 0;
			PosAndTexCoordinates[p++] = sin(endAngle);
			PosAndTexCoordinates[p++] = 1;
			PosAndTexCoordinates[p++] = (i + 1) / sectorsPerTextureSegments;
		}
	}

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	MatrixID = glGetUniformLocation(programID, "MVP");

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, arraySize * sizeof(GLfloat), PosAndTexCoordinates, GL_STATIC_DRAW);

	TextureManager::Inst()->LoadTexture("textures\\road.jpg", ROAD_IMAGE_ID);
}

void Road::Draw(const glm::mat4& viewMatrix) {
	glUseProgram(programID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	TextureManager::Inst()->BindTexture(ROAD_IMAGE_ID);

	glm::mat4 mvp = viewMatrix * getTransformMatrix();
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
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
		(void*)0            // array buffer offset
	);
	glDrawArrays(GL_TRIANGLES, 0, textureSegments * sectorsPerTextureSegments * 6);
	glDisableVertexAttribArray(0);
}