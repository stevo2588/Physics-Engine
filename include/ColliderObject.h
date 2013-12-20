#ifndef COLLIDEROBJECT_H
#define COLLIDEROBJECT_H

#include <CollidableObject.h>
#include <PBTime.h>
class Force;

#include <memory>

// A ColliderObject is an Object that can check for collisions with its collider Shapes
class ColliderObject : public CollidableObject {
public:
	typedef std::unique_ptr<CollidableObject> CollObjPtr;
	typedef std::unique_ptr<Force> ForcePtr;

	ColliderObject(Shape& collider) : CollidableObject(collider) {}

	virtual ForcePtr getCollisionForce(float timestep, float timestepFrac,
	                                   const CollidableObject& co, const Vector3D& normal) const
	{
		//return createDeferredForce(calcCollisionForce, normal);
		return ForcePtr();
	}

protected:
	virtual void update(const PBTime& theTime, CollidableObject& co) {}

	virtual Vector3D calcCollisionForce(Vector3D normal) {
		//return (-normal) * 10; 
	}

	virtual CollObjPtr clone() const { return CollObjPtr(new ColliderObject(*this)); }
};


#endif // COLLIDEROBJECT_H

