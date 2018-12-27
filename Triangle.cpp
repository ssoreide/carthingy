#include "Triangle.h"
#include "LoadShaders.h"
#include "TextureManager.h"
#include "Camera.h"
#include <iostream>

#define TRIANGLE_IMAGE_ID 1

static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f, 0, 0,
   1.0f, -1.0f, 0.0f, 1, 0,
   0.0f,  1.0f, 0.0f, 0.5, 1
};

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

void Triangle::Init() {
	programID = LoadShaders("TextureVertexShader.glsl", "TextureFragmentShader.glsl");

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	MatrixID = glGetUniformLocation(programID, "MVP");

	cameraPosID = glGetUniformLocation(programID, "cameraPos");

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	TextureManager::Inst()->LoadTexture("textures\\road.jpg", TRIANGLE_IMAGE_ID);
}

void Triangle::Draw(const Camera& cam) {
	glUseProgram(programID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	TextureManager::Inst()->BindTexture(TRIANGLE_IMAGE_ID);

	glm::mat4 mvp = cam.getViewProjection()*getTransformMatrix();
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glm::vec3 cpos = cam.getPosition();
	glUniform3f(cameraPosID, cpos[0], cpos[1], cpos[2]);
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
		(void*)0            // array buffer offset
	);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}