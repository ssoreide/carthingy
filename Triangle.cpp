#include "Triangle.h"
#include "LoadShaders.h"
#include "TextureManager.h"
#include <iostream>

#define TRIANGLE_IMAGE_ID 1

static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f, 0.0, 0.0,
   1.0f, -1.0f, 0.0f, 1.0, 0.0,
   0.0f,  1.0f, 0.0f, 0.5, 1.0
};

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

void Triangle::Init() {
	programID = LoadShaders("TextureVertexShader.glsl", "TextureFragmentShader.glsl");

	glGenVertexArrays(1, &myVAO);
	glBindVertexArray(myVAO);
	MatrixID = glGetUniformLocation(programID, "MVP");

	glGenBuffers(1, &myVBO);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	TextureManager::Inst()->LoadTexture("textures\\road3.jpg", TRIANGLE_IMAGE_ID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(float),  // stride 
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

void Triangle::Draw(const glm::mat4& viewMatrix) {
	glBindVertexArray(myVAO);
	glUseProgram(programID);
	glm::mat4 mvp = viewMatrix * getTransformMatrix();
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}