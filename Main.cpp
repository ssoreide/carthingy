#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>
#include "Triangle.h"
#include "Cube.h"
#include "Camera.h"
#include "Road.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "Skybox.h"
using namespace std;

const int width = 1920;
const int height = 1080;

Camera cam(width,height);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		cam.rotate(glm::vec3(-0.1, 0.0, 0.0));
	}
	else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		cam.rotate(glm::vec3(0.1, 0.0, 0.0));
	}
	else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		cam.rotate(glm::vec3(0, -0.1, 0.0));
	}
	else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		cam.rotate(glm::vec3(0, 0.1, 0.0));
	}
}

void printMatrix(glm::mat4 m) {
	cout << "Matrix:\n" << glm::to_string(m);

	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(m, scale, rotation, translation, skew, perspective);

	cout << "Scale: " << glm::to_string(scale) << "\n";
	cout << "rotation: " << glm::to_string(glm::eulerAngles(rotation)) << "\n";
	cout << "translation: " << glm::to_string(translation) << "\n";
	cout << "skew: " << glm::to_string(skew) << "\n";
	cout << "perspective: " << glm::to_string(perspective) << "\n\n";
}

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

	glfwSetKeyCallback(window, keyCallback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	cam.setPosition(glm::vec3(0, 1, 3));

	vector<Object*> objects;

	Road road;
	road.Init();
	road.setPosition(glm::vec3(0, 0, 0));
	road.setScaling(glm::vec3(5, 5, 4));
	objects.push_back(&road);

	Triangle t1;
	t1.Init();
	t1.setPosition(glm::vec3(0, 0, 0));
	t1.setScaling(glm::vec3(2, 2, 1));
	objects.push_back(&t1);

	Cube c1;
	c1.Init();
	c1.setPosition(glm::vec3(3, 0, 0));
	c1.setScaling(glm::vec3(1, 1, 1));
//	objects.push_back(&c1);

	Skybox skybox;
	skybox.Init();
	
	int error = glGetError();

	if (error != GL_NO_ERROR) {
		cout << "OpenGL error: " << error << "\n";
	}

	double scale = 0.0;
	double pos = 0;
//	cam.LookAt(t1.getTransformMatrix()[3]);

	cout << "Camera: " + glm::to_string(cam.getTransformMatrix()) + "\n";
	cam.setRotation(glm::vec3(0, 0, 0));
	cout << "After rotation: " + glm::to_string(cam.getTransformMatrix()) +"\n";

	error = glGetError();
	if (error != GL_NO_ERROR) {
		cout << "OpenGL error: " << error << "\n";
	}
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 6, 6), // Camera position
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	printMatrix(View);

	cam.setPosition(glm::vec3(0, 0, -8));
	cam.setRotation(glm::vec3(0.78, 0, 0));

	printMatrix(cam.getProjection());

	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 projectionView = cam.getProjection() * cam.getTransformMatrix();

//		cam.setRotation(glm::vec3(scale*2, 0 , scale));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox.Draw(cam.getProjection(), cam.getTransformMatrix());

		vector<Object*>::iterator it = objects.begin();
		while (it != objects.end()) {
			(*it)->Draw(projectionView);
			it++;
		}

//		road.setRotation(glm::vec3(0.0f, scale, 0.0f));
		t1.setRotation(glm::vec3(3.0f, 0.0f, -scale));

		glfwSwapBuffers(window);
		glfwPollEvents();

		scale -= 0.0005;
		pos = sin(scale);
	}

	glfwTerminate();
	return 0;
}