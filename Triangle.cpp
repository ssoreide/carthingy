#include "Triangle.h"
#include "LoadShaders.h"
#include "TextureManager.h"
#include "Camera.h"
#include <iostream>

#define TRIANGLE_IMAGE_ID 1

static const GLfloat g_vertex_buffer_data[] = {
// PosX   posY   posZ  U    V	 
   -1.0f, -1.0f, 0.0f, 0.0, 0.0,
    1.0f, -1.0f, 0.0f, 1.0, 0.0,
    0.0f,  1.0f, 0.0f, 0.5, 1.0
};

Triangle::Triangle()
{
	setTexture("textures\\road3.jpg");
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		5 * sizeof(float),  // stride 
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
}

void Triangle::Draw(const Camera& cam, const glm::mat4& transform) {
	Object::Draw(cam, transform);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}