#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <Physical.h>
#include <Utility.h>
class Force;


class RigidBody : public Physical {
public:
	typedef std::unique_ptr<Force> ForcePtr;
	typedef std::unique_ptr<CollidableObject> CollObjPtr;
	typedef std::unique_ptr<Physical> PhysPtr;
	typedef std::reference_wrapper<const Force> ForceRef;

	RigidBody(const Object& parent, Shape& collider, float mass, const Vector3D& cog,
	          float fric, float elasticity, const Vector3D& velocity);

	RigidBody(const Object& parent, const Vector3D& pos, Shape& collider, float mass,
	          const Vector3D& cog, float fric, float elasticity, const Vector3D& velocity);
	
	
	ForcePtr getCollisionForce(float timestep, float timestepFrac,
	                           const CollidableObject& updated, const Vector3D& normal) const;

private:
	virtual void update(const PBTime& theTime, Physical& p,
	                const std::vector<ForceRef>& forces, const std::vector<ForceRef>& accels);

	Vector3D calcCollisionForce(const PBTime& theTime, float timestepFrac, Vector3D normal,
	                            float mass0, float fric0, float elastic0, Vector3D vel0,
	                            float mass1, float fric1, float elastic1, Vector3D vel1) const;
	
	virtual CollObjPtr clone() const { return CollObjPtr(new RigidBody(*this)); }

	virtual PhysPtr clonePhys() const { return PhysPtr(new RigidBody(*this)); }

	float mass;
	Vector3D cog;
	float friction; // 0 - 1
	float elasticity; // 0 - 1
	Vector3D velocity; 
};


#endif // RIGIDBODY_H

