#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <Physical.h>
#include <Shape.h>
#include <Utility.h>
class Force;


class RigidBody : public Physical {
public:
	typedef std::unique_ptr<Force> ForcePtr;
	typedef std::unique_ptr<CollidableObject> CollObjPtr;
	typedef std::unique_ptr<Physical> PhysPtr;
	typedef std::reference_wrapper<const Force> ForceRef;

	RigidBody(Shape& collider, float mass, const Vector3D& cog, float fric, float elasticity,
	          const Vector3D& velocity)
	: Physical(collider), mass(mass), cog(cog), friction(fric), elasticity(elasticity),
	  velocity(velocity)
	{
	}
	
	
	ForcePtr getCollisionForce(float timestep, float timestepFrac,
	                           const CollidableObject& updated, const Vector3D& normal) const
	{
		using namespace std::placeholders; // adds visibility of _1

		const RigidBody& rb = static_cast<const RigidBody&>(updated); 

		std::function<Vector3D (const PBTime&)> func =
		                                  std::bind( &RigidBody::calcCollisionForce, this,
		                                  _1, timestepFrac, normal,
		                                  mass, friction, elasticity, velocity,
		                                  rb.mass, rb.friction, rb.elasticity, rb.velocity );

		return ForcePtr( new DeferredForce(func) );

		//return createDeferredForce( func );
	}

private:
	virtual void update(const PBTime& theTime, Physical& p,
	                    const std::vector<ForceRef>& forces, const std::vector<ForceRef>& accels)
	{
		RigidBody& rb = static_cast<RigidBody&>(p); // TODO: check on this...

		float timestep = theTime.getTimestep();
		float currentTime = theTime.getElapsedTime();

		//-------------- Get the forces at this time and calc the acceleration ----------
		size_t fSize = forces.size();
		size_t aSize = accels.size();

		Vector3D netAccel;
		// calculate net acceleration
		for(int i=0; i<fSize; i++) {
			netAccel += forces[i].get().get(theTime);
		}
		netAccel = netAccel/mass;
		for(int i=0; i<aSize; i++) {
			netAccel += accels[i].get().get(theTime);
		}

		//------------- Update the velocity and the position for this time -----------
		rb.transform.translate(rb.velocity * timestep);
		rb.velocity += netAccel * timestep;
	}

	Vector3D calcCollisionForce(const PBTime& theTime, float timestepFrac, Vector3D normal,
	                            float mass0, float fric0, float elastic0, Vector3D vel0,
	                            float mass1, float fric1, float elastic1, Vector3D vel1) const
	{
		float timestep = theTime.getTimestep();

		// Get velocity at time of collision
		Vector3D vc = vel0 + ((vel1 - vel0) * timestepFrac);
		
		// Get velocity immediately after collision
		Vector3D vn = normal * vc.dotProduct(normal);
		Vector3D vt = vc - vn;
		Vector3D vnPrime = vn * -elastic0;
		Vector3D vtPrime = vt * (1 - fric0); // TODO LATER: implement more accurate model

		Vector3D newVelocity = vnPrime + vtPrime;

		return ((newVelocity - vel0)/(timestep)) * mass0;
	}

	virtual CollObjPtr clone() const { return CollObjPtr(new RigidBody(*this)); }

	virtual PhysPtr clonePhys() const { return PhysPtr(new RigidBody(*this)); }

	float mass;
	Vector3D cog;
	float friction; // 0 - 1
	float elasticity; // 0 - 1
	Vector3D velocity; 
};


#endif // RIGIDBODY_H

