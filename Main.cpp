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

Camera *cam = NULL;

bool key_up = false;
bool key_down = false;
bool key_left = false;
bool key_right = false;

void update_from_keys() {
	if (cam!=NULL) {
		if (key_up) {
			cam->addVelocity(-0.1f);
		}
		if (key_down) {
			cam->addVelocity(0.1f);
		}
		if (key_left) {
			cam->rotate(glm::vec3(0, 0.01f, 0.0f));
		}
		if (key_right) {
			cam->rotate(glm::vec3(0, -0.01f, 0.0f));
		}
	}
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_UP) {
		key_up = (action == GLFW_PRESS || action == GLFW_REPEAT);
	}
	else if (key == GLFW_KEY_DOWN) {
		key_down = (action == GLFW_PRESS || action == GLFW_REPEAT);
	}
	else if (key == GLFW_KEY_LEFT) {
		key_left = (action == GLFW_PRESS || action == GLFW_REPEAT);
	}
	else if (key == GLFW_KEY_RIGHT) {
		key_right = (action == GLFW_PRESS || action == GLFW_REPEAT);
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
	cout << "Starting...\n";
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

	cam = new Camera(width, height);

	vector<Object*> objects;

	Road road;
	road.setPosition(glm::vec3(0, 0, 0));
	road.setScaling(glm::vec3(15, 15, 15));
	objects.push_back(&road);

	Triangle t1;
	t1.setPosition(glm::vec3(0, 2, 0));
	t1.setScaling(glm::vec3(2, 2, 1));

	Cube tc1;
	tc1.setPosition(glm::vec3(1, 0, 0));
	tc1.setScaling(glm::vec3(0.2, 0.2, 0.2));
	t1.addChild(&tc1);

	Cube tc2;
	tc2.setPosition(glm::vec3(-1, 0, 0));
	tc2.setScaling(glm::vec3(0.2, 0.2, 0.2));
	t1.addChild(&tc2);

	objects.push_back(&t1);

	Cube c1;
	c1.setPosition(glm::vec3(-3, 0, 0));
	c1.setScaling(glm::vec3(1, 1, 1000));
//	objects.push_back(&c1);

	Cube c2;
	c2.setPosition(glm::vec3(3, 0, 0));
	c2.setScaling(glm::vec3(1, 1, 1));
//	objects.push_back(&c2);

	Cube c3;
	c3.setPosition(glm::vec3(0, 0, -5));
	c3.setScaling(glm::vec3(0.5, 0.5, 0.5));
//	objects.push_back(&c3);

	Skybox skybox;

	int error = glGetError();

	if (error != GL_NO_ERROR) {
		cout << "OpenGL error: " << error << "\n";
	}

	double scale = 0.0;
	double pos = 0;

	cam->setPosition(glm::vec3(0, 2, 20));
	cam->setRotation(glm::vec3(0, 3.1415,0));

	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 projectionView = cam->getProjection() * glm::inverse(cam->getTransformMatrix());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox.Draw(cam->getProjection(), cam->getTransformMatrix());

		vector<Object*>::iterator it = objects.begin();
		while (it != objects.end()) {
			(*it)->Draw(*cam, glm::mat4(1));
			it++;
		}

		t1.setRotation(glm::vec3(3.0f, 0.0f, -scale));

		glfwSwapBuffers(window);
		glfwPollEvents();

		scale -= 0.0005;
		pos = sin(scale);
		update_from_keys();
		cam->move(0.02f);
	}

	glfwTerminate();
	return 0;
}