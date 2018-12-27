#include "Road.h"
#include "LoadShaders.h"
#include <math.h>
#include <iostream>

using namespace std;

/*static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, 0, 0.5f,
	1.0f, 0, 0.5f,
	0.3f,  0, 0.0f,
};*/

int numberSegments = 100;

Road::Road()
{
}


Road::~Road()
{
}

void Road::Init() {
	programID = LoadShaders("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");
	std::cout << "Road programID: " << programID << "\n";

	int n = numberSegments;
	float widthFactor = 0.8;
	float pi = atan(1) * 4;
	int vps = 6; //vertices per segment
	int cps = 3 * vps; //components per segment

	GLfloat *vertexCoordinates = new GLfloat[n * 18];

	for (int i = 0; i < n; i ++) {
		int p = i * cps;
		// TRIANGLE 1
		vertexCoordinates[p] = cos(i * 2 * pi / n);
		vertexCoordinates[p + 2] = 0;
		vertexCoordinates[p + 1] = sin(i * 2 * pi / n);
						  
		vertexCoordinates[p + 3] = cos(i * 2 * pi / n) * widthFactor;
		vertexCoordinates[p + 5] = 0;
		vertexCoordinates[p + 4] = sin(i * 2 * pi / n) * widthFactor;
						  
		vertexCoordinates[p + 6] = cos((i + 1) * 2 * pi / n);
		vertexCoordinates[p + 8] = 0;
		vertexCoordinates[p + 7] = sin((i + 1) * 2 * pi / n);

		// TRIANGLE 2

	}

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	MatrixID = glGetUniformLocation(programID, "MVP");

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, n * 18 * sizeof(GLfloat), vertexCoordinates, GL_STATIC_DRAW);
}

void Road::Draw(const glm::mat4& viewMatrix) {
	glUseProgram(programID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glm::mat4 mvp = viewMatrix * getTransformMatrix();
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glDrawArrays(GL_TRIANGLES, 0, numberSegments*6);
	glDisableVertexAttribArray(0);
}