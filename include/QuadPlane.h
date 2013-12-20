#ifndef QUADPLANE_H
#define QUADPLANE_H

#include <Shape.h>
#include <Utility.h>

class QuadPlane : public Shape {
public:
	QuadPlane(const Vector3D& normal, float width, float depth) 
	    : normal(normal), width(width), depth(depth), halfWidth(width/2), halfDepth(depth/2) {}

	Vector3D getNorm() const { return normal; }
	float getWidth() const { return width; }
	float getDepth() const { return depth; }

	void openGLDraw() const;

	const QuadPlane& convert(const Shape& s) const {
		return static_cast<const QuadPlane&>(s);
	}

protected:
	Vector3D normal;
	float width, depth;
	float halfWidth, halfDepth;
};


#endif // QUADPLANE_H

