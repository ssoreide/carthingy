#include "Skybox.h"
#include "LoadShaders.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;

vector<std::string> faces
{
	"skybox/right.jpg",
		"skybox/left.jpg",
		"skybox/top.jpg",
		"skybox/bottom.jpg",
		"skybox/front.jpg",
		"skybox/back.jpg"
};

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

unsigned int Skybox::loadCubemap(vector<string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

Skybox::Skybox() {

}
Skybox::~Skybox() {

}

void Skybox::Init() {
	cubemapTexture = loadCubemap(faces);

	programID = LoadShaders("SkyboxVertexShader.glsl", "SkyboxFragmentShader.glsl");

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	MatrixID = glGetUniformLocation(programID, "MVP");

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

}

void Skybox::Draw(const glm::mat4& viewMatrix) {
	glDepthMask(GL_FALSE);
	glUseProgram(programID);
//	skyboxShader.use();
	// ... set view and projection matrix
	//glBindVertexArray(skyboxVAO);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDepthMask(GL_TRUE);
	// ... draw rest of the scene

	// under her
	//glUseProgram(programID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

	glm::mat4 mvp = viewMatrix;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
/*	glVertexAttribPointer(
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
	);*/
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDepthMask(GL_TRUE);
	glDisableVertexAttribArray(0);
}