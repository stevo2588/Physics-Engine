#ifndef OBJECT_H
#define OBJECT_H

#include <Utility.h>
#include <PBTransform.h>
#include <Renderable.h>

// An Object has a PBTransform and a Renderable.

class Object {
public:
	Object() : renderable(NULL) {}
	Object(const Vector3D& pos) : transform(pos.elements[0], pos.elements[1], pos.elements[2]),
	                              renderable(NULL)
	{}

	// TODO LATER: Game/Draw update() function?

	void setRenderable(Renderable* r) { renderable = r; }
	const Renderable* getRenderable() const { return renderable; }

	PBTransform transform;

protected:
	Renderable* renderable;
};

#endif // OBJECT_H

