#include <iostream>
#include "Skybox.h"
#include "TextureManager.h"
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include "Square.h"
#include "Cube.h"
#include "Road.h"
#include <glm/gtx/rotate_vector.hpp>
#include "Camera.h"
#include <math.h>

const int width = 1920;
const int height = 1080;

float PI = (float)atan(1) * 4;

Camera *cam = NULL;
Skybox *skybox = NULL;

vector<glm::vec3> track_lights;

using namespace std;
float r = 0.05f;
float red = 1, green = 1, blue = 1;

bool key_up = false;
bool key_down = false;
bool key_left = false;
bool key_right = false;
bool key_s = true;
bool key_l = true;
bool key_n = true;
bool key_c = true;

void update_from_keys() {
	if (cam != NULL) {
		if (key_up) {
			cam->addVelocity(-0.1f);
		}
		if (key_down) {
			cam->addVelocity(0.1f);
		}
		if (key_left) {
			cam->rotate(glm::vec3(0, (PI / 180) / 4.0f, 0.0f));
		}
		if (key_right) {
			cam->rotate(glm::vec3(0, -(PI / 180)/ 4.0f, 0.0f));
		}
	}
}

vector<Object*> objects; // All objects in our scene
Cube *cube;
Square *square;
Road *road;

void setCarLights() {
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(glm::vec4(0, 2, 0, 1))); // 1 in the w makes it spot instead of directional
	glLightfv(GL_LIGHT1, GL_AMBIENT, glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
	glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(glm::vec3(1, 1, 1)));
	glLightfv(GL_LIGHT1, GL_SPECULAR, glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, glm::value_ptr(glm::vec3(0, -0.1, -1)));
}

void setTrackLight(int light) {
	glEnable(light);
	glLightfv(light, GL_AMBIENT, glm::value_ptr(glm::vec3(0.0, 0.0, 20.0)));
	glLightfv(light, GL_DIFFUSE, glm::value_ptr(glm::vec3(0.5, 0.5, 20.2)));
	glLightfv(light, GL_SPECULAR, glm::value_ptr(glm::vec3(0, 0, 20)));
	glLightfv(light, GL_SPOT_DIRECTION, glm::value_ptr(glm::vec3(0, -1, 0)));
	glLightf(light, GL_SPOT_CUTOFF, 45);
	glLightf(light, GL_SPOT_EXPONENT, 10);
}

void setStaticLights() {

	// Luna
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(glm::vec4(0, 10, 0, 0))); // 1 in the w makes it spot instead of directional
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(glm::vec3(0.05, 0.05, 0.05)));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(glm::vec3(0.05, 0.05, 0.05)));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(glm::vec3(0, 0, 0)));

	// Track Lights
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(road->getTransformMatrix()));
	for (unsigned int i = 0; i < track_lights.size(); i++) {
		glPushMatrix();
		glTranslatef(track_lights[i].x, track_lights[i].y, track_lights[i].z);
		glutSolidTeapot(0.3);
		glPopMatrix();

	}
	setTrackLight(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, glm::value_ptr(glm::vec4(track_lights[0], 1))); // 1 in the w makes it spot instead of directional
	setTrackLight(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_POSITION, glm::value_ptr(glm::vec4(track_lights[1], 1))); // 1 in the w makes it spot instead of directional
	setTrackLight(GL_LIGHT4);
	glLightfv(GL_LIGHT4, GL_POSITION, glm::value_ptr(glm::vec4(track_lights[2], 1))); // 1 in the w makes it spot instead of directional
	setTrackLight(GL_LIGHT5);
	glLightfv(GL_LIGHT5, GL_POSITION, glm::value_ptr(glm::vec4(track_lights[3], 1))); // 1 in the w makes it spot instead of directional
	glPopMatrix();

}

void MyRenderFunction(void)
{
	update_from_keys();

	road->takeOffTexture(key_s);

	cam->move(0.1f);
	int win = glutGetWindow();
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Reset transformations
	glLoadIdentity();

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (key_s) {
		skybox->Draw(cam->getProjection(), cam->getTransformMatrix());
		setCarLights();
	}
	else {
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_DENSITY, 0.04);
		glFogf(GL_FOG_START, 1);
		glFogf(GL_FOG_END, 400);
		float fog_color[] = { 1,1,1,0 };
		glFogfv(GL_FOG_COLOR, fog_color);
		glFogi(GL_FOG_COORD_SRC, GL_FRAGMENT_DEPTH);
	}
	glMultMatrixf(glm::value_ptr(glm::inverse(cam->getTransformMatrix())));
	if (key_s) {
		setStaticLights();
	}

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(glm::vec3(0, 0, 0)));
	glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(glm::vec3(0.8, 0.8, 0.8)));

	cube->rotate(glm::vec3(0.001, 0.002, 0));
	square->rotate(glm::vec3(0.001, 0.002, 0));

	vector<Object*>::iterator it = objects.begin();
	while (it != objects.end()) {
		(*it)->Draw();
		it++;
	}

	glutSwapBuffers();
	glutPostWindowRedisplay(win);
}

void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = 1.0f* w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}
// use this for letters
void processNormalKeys(unsigned char key, int x, int y) {
	cout << "Letter key pressed: " << key << "\n";
	switch (key) {
	case 27: // escape
		exit(0);
	case 's':
		cout << "toggling s key\n";
		key_s = !key_s;
		break;
	case 'l':
		key_l = !key_l;
		break;
	case 'n':
		key_n = !key_n;
		break;
	case 'c':
		key_c = !key_c;
		break;
	}
}

void processSpecialKeys(int key, int x, int y) {
	cout << "Key: " << key << " x: " << x << ", y: " << y << "\n";

	switch (key) {
	case GLUT_KEY_LEFT:
		key_left = true;
		break;
	case GLUT_KEY_RIGHT:
		key_right = true;
		break;
	case GLUT_KEY_UP:
		key_up = true;
		break;
	case GLUT_KEY_DOWN:
		key_down = true;
		break;
	}
}

void processSpecialKeysUp(int key, int x, int y) {
	cout << "UpKey: " << key << " x: " << x << ", y: " << y << "\n";

	switch (key) {
	case GLUT_KEY_LEFT:
		key_left = false;
		break;
	case GLUT_KEY_RIGHT:
		key_right = false;
		break;
	case GLUT_KEY_UP:
		key_up = false;
		break;
	case GLUT_KEY_DOWN:
		key_down = false;
		break;
	}
}


int main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(width, height);

	int argc = 1; // Dummy parameters for glutInit
	char *argv[1] = { (char*)"Nothing" };

	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);


	int mainwin = glutCreateWindow("Car Game");

	// Initialize GLEW (for skybox / shader loading)
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		return -1;
	}

	cam = new Camera(width, height);
	cam->setPosition(glm::vec3(0, 2, 0));
	cam->setRotation(glm::vec3(0, 0, 0));

	TextureManager::Inst()->LoadTexture("textures/cola.jpg");

	skybox = new Skybox();

	glutDisplayFunc(MyRenderFunction);
	glutReshapeFunc(changeSize);
	glutIdleFunc(MyRenderFunction);
	glutSpecialFunc(processSpecialKeys);
	glutSpecialUpFunc(processSpecialKeysUp);
	glutKeyboardFunc(processNormalKeys);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	cube = new Cube();
	cube->setPosition(glm::vec3(0, 0, -20));
	cube->setScaling(glm::vec3(0.5, 0.5, 0.5));
	//cube->setRotation(glm::vec3(0, 3.14/4, 0));
	cube->setTexture("textures/cola.jpg");
	//	objects.push_back(cube);

	square = new Square();
	square->setPosition(glm::vec3(0, 3, -50));
	square->setScaling(glm::vec3(1, 1, 1));
	square->setRotation(glm::vec3(0, 0, 0));
	square->setTexture("textures/cola.jpg");
	//	objects.push_back(square);

	road = new Road();
	road->setPosition(glm::vec3(0, 0, 0));
	road->setScaling(glm::vec3(15, 15, 15));
	track_lights = road->getTrackLights();
	objects.push_back(road);

	Square t1;
	t1.setPosition(glm::vec3(0, 0, -40));
	t1.setScaling(glm::vec3(15, 15, 15));
	t1.setTexture("textures/cola.jpg");
	objects.push_back(&t1);

	Square *t2 = new Square();
	t2->setPosition(glm::vec3(0, 0, -5));
	t2->setScaling(glm::vec3(2, 2, 2));
	t2->setRotation(glm::vec3(3.14 / 2, 0, 0));
	t2->setTexture("textures/cola.jpg");
	cube->addChild(t2);

	Cube tc1;
	tc1.setPosition(glm::vec3(1, 0, 0));
	tc1.setScaling(glm::vec3(-0.2, -0.2, -0.2));
	//	t1.addChild(&tc1);

	Cube tc2;
	tc2.setPosition(glm::vec3(-1, 0, 0));
	tc2.setScaling(glm::vec3(0.2, 0.2, 0.2));
	//	t1.addChild(&tc2);

		// testgreiene
	Cube c1;
	c1.setPosition(glm::vec3(-3, 5, 0));
	c1.setScaling(glm::vec3(1, 1, 100));
	//	objects.push_back(&c1);

	Cube c2;
	c2.setPosition(glm::vec3(3, 0, 0));
	c2.setScaling(glm::vec3(1, 1, 1));
	//	objects.push_back(&c2);

	Cube c3;
	c3.setPosition(glm::vec3(0, 0, -5));
	c3.setScaling(glm::vec3(0.5, 0.5, 0.5));
	//	objects.push_back(&c3);

	glutMainLoop();

	return 0;
}


