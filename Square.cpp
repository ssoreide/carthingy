#pragma once
#include "Square.h"
#include "LoadShaders.h"
#include "TextureManager.h"
#include "Camera.h"
#include <iostream>

static const GLfloat g_vertex_buffer_data[] = {
	// PosX   posY   posZ  U    V  Normal	
	-1.0f, -1.0f, 0.0f, 0.0, 0.0, 0, 0, -1,
	1.0f, -1.0f, 0.0f, 1.0, 0.0,  0, 0, -1,
	1.0f,  1.0f, 0.0f, 1.0, 1.0,  0, 0, -1,
	1.0f,  1.0f, 0.0f, 1.0, 1.0,  0, 0, -1,
	-1.0f, 1.0f, 0.0f, 0.0, 1.0,  0, 0, -1,
	-1.0f, -1.0f, 0.0f, 0.0, 0.0, 0, 0, -1,
};

Square::Square()
{
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),  // stride 
		(void*)0            // array buffer offset
	);
	glVertexAttribPointer(
		2,                  // attribute 2 (UV)
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),  // stride
		(void*)(3 * sizeof(float))  // array buffer offset
	);
	glVertexAttribPointer(
		1,                  // attribute 2 (Normals)
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),  // stride
		(void*)(5 * sizeof(float))  // array buffer offset
	);
	glBindVertexArray(0);
}

void Square::Draw(const Camera& cam, const glm::mat4& transform) {
	Object::Draw(cam, transform);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}