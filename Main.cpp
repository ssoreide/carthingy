#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include "Triangle.h"
#include "Cube.h"
#include "Camera.h"
#include "Road.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

const int width = 1920;
const int height = 1080;

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(width, height, "Test", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Camera cam;
	cam.setPosition(glm::vec3(0, 1, 3));

	vector<Object*> objects;

	Road road;
	road.Init();
	road.setPosition(glm::vec3(0, 0, 0));
	road.setScaling(glm::vec3(4, 4, 4));
	objects.push_back(&road);

	Triangle t1;
	t1.Init();
	t1.setPosition(glm::vec3(0, 0, 0));
	t1.setScaling(glm::vec3(0.4, 0.4, 0.4));
	//objects.push_back(&t1);

	double scale = 0.0;
	double pos = 0;
//	cam.LookAt(t1.getTransformMatrix()[3]);

	cout << "Camera: " + glm::to_string(cam.getTransformMatrix()) + "\n";
	cam.setRotation(glm::vec3(0, 0, 0));
	cout << "After rotation: " + glm::to_string(cam.getTransformMatrix()) +"\n";

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width/height, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 View = glm::lookAt(
			glm::vec3(0, 6, -6), // Camera position
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		glm::mat4 projectionView = Projection * View;

		cam.setRotation(glm::vec3(scale, 0 , 0));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vector<Object*>::iterator it = objects.begin();
		while (it != objects.end()) {
			(*it)->Draw(projectionView);
			it++;
		}

		road.setRotation(glm::vec3(0.0f, 0.0f, scale));

		glfwSwapBuffers(window);
		glfwPollEvents();

		scale -= 0.0005;
		pos = sin(scale);
	}

	glfwTerminate();
	return 0;
}