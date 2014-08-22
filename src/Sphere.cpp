#include <Sphere.h>

#include <GL/glew.h>
//#include <SFML/OpenGL.hpp>

#include <cmath>

/*
Equation of a sphere with center at (x0,y0,z0) and radius r:
(x - x0)^2 + (y - y0)^2 _ (z - z0)^2 = r^2
*/

// TODO LATER: have a way to set the mesh resolution
void Sphere::openGLDraw() const {
	const double PI = 3.1415926;
	int lats=10, longs=10;

	for(int i = 0; i <= lats; i++) {
		double lat0 = PI * (-0.5 + (double) (i - 1) / lats);
		double z0   = sin(lat0);
		double zr0  = cos(lat0);

		double lat1 = PI * (-0.5 + (double) i / lats);
		double z1   = sin(lat1);
		double zr1  = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <= longs; j++) {
			double lng = 2 * PI * (double) (j - 1) / longs;
			double x   = cos(lng);
			double y   = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}

