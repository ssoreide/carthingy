#pragma once
#include "Square.h"
#include "TextureManager.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Square::Square()
{
}

void Square::Draw() {
	DrawChildren();
	UpdateMaterial();
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(getTransformMatrix()));

	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0, 0); glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2d(1, 0); glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2d(1, 1); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2d(0, 1); glVertex3f(-1.0, 1.0, 0.0);
	glEnd();
	glPopMatrix();
}