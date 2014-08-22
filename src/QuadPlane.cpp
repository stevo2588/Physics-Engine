#include <QuadPlane.h>

#include <GL/glew.h>
//#include <SFML/OpenGL.hpp>

#include <iostream>


void QuadPlane::openGLDraw() const {
	glBegin(GL_QUADS);
		glNormal3f(normal.elements[0], normal.elements[1], normal.elements[2]);
		glVertex3f(-halfWidth, 0, -halfDepth);
		glNormal3f(normal.elements[0], normal.elements[1], normal.elements[2]);
		glVertex3f(-halfWidth, 0, halfDepth);
		glNormal3f(normal.elements[0], normal.elements[1], normal.elements[2]);
		glVertex3f(halfWidth, 0, halfDepth);
		glNormal3f(normal.elements[0], normal.elements[1], normal.elements[2]);
		glVertex3f(halfWidth, 0, -halfDepth);
	glEnd();
}


