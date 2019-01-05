#include "Cube.h"
#include "TextureManager.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube()
{
}

void Cube::Draw() {
	DrawChildren();
	UpdateMaterial();
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(getTransformMatrix()));
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(glm::vec3(1, 0, 0)));
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(glm::vec3(0, 1, 0)));
	//	glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(glm::vec3(0, 0, 1)));

	glBegin(GL_QUADS);

	// Front Rectangle
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0); glVertex3f(-0.5, -0.5, 0.5); // Nede, venstre
	glTexCoord2d(1, 0); glVertex3f(0.5, -0.5, 0.5); // nede, høyre
	glTexCoord2d(1, 1); glVertex3f(0.5, 0.5, 0.5); // oppe, høyre
	glTexCoord2d(0, 1); glVertex3f(-0.5, 0.5, 0.5); // oppe, venstre

	// Right Rectangle
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2d(0, 0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2d(1, 0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2d(1, 1); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, 0.5);

	// Left Rectangle
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2d(0, 0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2d(1, 0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2d(1, 1); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2d(0, 1); glVertex3f(-0.5, -0.5, -0.5);

	// Back Rectangle
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2d(0, 0); glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2d(1, 0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2d(1, 1); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2d(0, 1); glVertex3f(0.5, -0.5, -0.5);

	// Top Rectangle
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2d(0, 0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2d(1, 0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2d(1, 1); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2d(0, 1); glVertex3f(-0.5, 0.5, 0.5);

	// Bottom Rectangle
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2d(0, 0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2d(1, 0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2d(1, 1); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2d(0, 1); glVertex3f(-0.5, -0.5, -0.5);

	glEnd();
	glPopMatrix();
}