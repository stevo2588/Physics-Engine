#ifndef COLLIDABLEOBJECT_H
#define COLLIDABLEOBJECT_H

#include <Object.h>
#include <Shape.h>
#include <PBTime.h>
class Force;

#include <memory>


// CollidableObject is an object that can detect collisions and return a CollisionForce.
class CollidableObject : public Object {
public:
	typedef std::unique_ptr<CollidableObject> CollObjPtr;
	typedef std::unique_ptr<Force> ForcePtr;
	typedef std::reference_wrapper<Shape> ShapeRef;

	// Updates this CollidableObject
	void update(const PBTime& theTime);

	CollObjPtr getUpdated(const PBTime& theTime);

	// Get the force this object exerts during collision
	// NOTE: the timestep at which the collision occurred is at timestep*timestepFrac
	virtual ForcePtr getCollisionForce(float timestep, float timestepFrac,
	                           const CollidableObject& updated, const Vector3D& normal)const=0;

	// Checks for a collision with the CollidableObject that would occur in the given timestep.
	// Returns whether a collision would happen, the fraction of the timestep at which it
	// would happen, and the collision force that this object would receive as a result of the
	// collision.
	bool collisionCheck(float timestep, const CollidableObject& thisUpdated,
	                    const CollidableObject& other, const CollidableObject& otherUpdated,
	                    float& timestepFrac, ForcePtr& thisCollForce, ForcePtr& otherCollForce);
	
	void addCollider(Shape& c) {
		collider = ShapeRef(c);
	}
 
protected:
	CollidableObject(const Object& parent, Shape& collider)
	: Object(parent), collider(collider) {}
	CollidableObject(const Object& parent, const Vector3D& pos, Shape& collider)
	: Object(pos,parent), collider(collider) {}

	virtual void update(const PBTime& theTime, CollidableObject& co)=0;

	virtual CollObjPtr clone() const=0;

	// TODO LATER: create Collider class so that collider doesn't have to be a shape
	ShapeRef collider;

	/*
	<typename T1, typename T2>
	bool collisionWith(const T1& other, const T1& otherUpdated,
	                   const T2& thisUpdated,
	                   float& timestepFrac, CollisionForce& collisionForce)
	{
		return CollisionHandler::collision(*this, thisUpdated, other, otherUpdated,
		                                   timestepFrac, collisionForce);
	}
	*/
};


#endif // COLLIDABLEOBJECT_H

