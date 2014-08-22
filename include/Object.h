#ifndef OBJECT_H
#define OBJECT_H

#include <Utility.h>
#include <PBTransform.h>
#include <Renderable.h>

// An Object has a PBTransform and a Renderable.

class Object {
public:
	// Default constructor should only be used to create WORLD node
	Object();

	Object(const Object& parent);

	Object(const Vector3D& pos, const Object& parent);

	void setRenderable(Renderable* r) { renderable = r; }
	const Renderable* getRenderable() const { return renderable; }

	PBObjectTransform transform;

protected:
	Renderable* renderable;
};

#endif // OBJECT_H

