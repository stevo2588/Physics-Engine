#ifndef SPHERE_H
#define SPHERE_H

#include <Shape.h>
#include <Utility.h>

class Sphere : public Shape {
public:
	Sphere(float r) : radius(r), radiusSq(r*r) {}

	float getRad() const { return radius; }

	// Given a point on the sphere (world coordinates) return the normal
	Vector3D getNormalFromWorld(const Vector3D& p) const {
		return Vector3D((p - transform.getPos())/radius);
	}

	const Sphere& convert(const Shape& s) const {
		return static_cast<const Sphere&>(s);
	}

	void openGLDraw() const;
	
protected:
	float radius;
	double radiusSq;
};


#endif // SPHERE_H
