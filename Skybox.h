#pragma once
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "FreeImage.h"
#include <iostream>
#include <string>
#include "TextureManager.h"
using namespace std;

class Skybox {
public:
	Skybox();
	~Skybox();

	unsigned int loadCubemap(vector<string> faces);
	virtual void Init();
	virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

private:
	GLuint programID; // Shader program id
	GLuint myVBO;
	GLuint ProjectionID;
	GLuint ViewID;
	GLuint myVAO;
	unsigned int cubemapTexture;

};