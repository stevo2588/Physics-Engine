#include <cmath>
#include <Sphere.h>

/*
Equation of a sphere with center at (x0,y0,z0) and radius r:
(x - x0)^2 + (y - y0)^2 _ (z - z0)^2 = r^2
*/

// Given a point on the sphere (world coordinates) return the normal
Vector3D Sphere::getNormalFromWorld(const Vector3D& p) const {
   return Vector3D((p - getPos())/radius);
}

// TODO LATER: have a way to set the mesh resolution
void Sphere::openGLDraw() const {
	int lats=10, longs=10;

	glMultTransposeMatrixf(transform.getElements());
	for(int i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
		double z0  = sin(lat0);
		double zr0 =  cos(lat0);

		double lat1 = M_PI * (-0.5 + (double) i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double) (j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}

