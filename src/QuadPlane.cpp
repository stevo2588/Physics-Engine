#include <QuadPlane.h>

#include <Renderable.h>

#include <SFML/OpenGL.hpp>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

void QuadPlane::openGLDraw() const {
	double e[4][4];
	transform.getTransform().getElements(e);
	glMultTransposeMatrixf(e);
	//glLoadTransposeMatrixf(e);
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

