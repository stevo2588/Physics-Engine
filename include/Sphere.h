#ifndef SPHERE_H
#define SPHERE_H

#include <Shape.h>
#include <Utility.h>

class Sphere : public Shape {
public:
	Sphere(float r) : radius(r), radiusSq(r*r) {}

	float getRad() const { return radius; }

	const Sphere& convert(const Shape& s) const {
		return static_cast<const Sphere&>(s);
	}

	void openGLDraw() const;
	
protected:
	float radius;
	double radiusSq;
};


#endif // SPHERE_H
