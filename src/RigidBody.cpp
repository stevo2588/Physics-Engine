
#include <RigidBody.h>

#include <Shape.h>


RigidBody::RigidBody(const Object& parent, Shape& collider, float mass, const Vector3D& cog,
                     float fric, float elasticity, const Vector3D& velocity)
: Physical(parent,collider), mass(mass), cog(cog), friction(fric), elasticity(elasticity),
  velocity(velocity)
{
}

RigidBody::RigidBody(const Object& parent, const Vector3D& pos, Shape& collider, float mass,
                     const Vector3D& cog, float fric, float elasticity,
                     const Vector3D& velocity)
: Physical(parent,pos,collider), mass(mass), cog(cog), friction(fric), elasticity(elasticity),
  velocity(velocity)
{
}

ForcePtr RigidBody::getCollisionForce(float timestep, float timestepFrac,
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


void RigidBody::update(const PBTime& theTime, Physical& p,
					const std::vector<ForceRef>& forces, const std::vector<ForceRef>& accels)
{
	RigidBody& rb = static_cast<RigidBody&>(p); // TODO: check on this...

	float timestep = theTime.getTimestep();
	float currentTime = theTime.getElapsedTime();

	//-------------- Get the forces at this time and calc the acceleration ----------

	Vector3D netAccel;
	// calculate net acceleration
	for( auto &f: forces ) {
		netAccel += f.get().get(theTime);
	}
	netAccel = netAccel/mass;
	for( auto &a: accels ) {
		netAccel += a.get().get(theTime);
	}

	//------------- Update the velocity and the position for this time -----------
	rb.transform.translate(rb.velocity * timestep);
	rb.velocity += netAccel * timestep;
}


Vector3D RigidBody::calcCollisionForce(const PBTime& theTime, float timestepFrac, Vector3D normal,
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


/*
// TODO NOW
// Update the current state of the RigidBody
void RigidBody::update(const std::vector<Force>& forces,
					const std::vector<Force>& accels, const std::vector<ColliderObject>& co, 
					float timestep, float currentTime)
{
	// check for collision at new position
	float timestepRemain = timestep;
	float timestepFrac = 1.0f;
	float cTime = currentTime - timestep;
	Vector3D collisionForce(0,0,0);

	while(timestepRemain > 0) {
		//--------- Calculate potential position --------------
		Vector3D newPos = pos + velocity * timestepRemain;

		//---------------- If collision -----------------------
		if(earliestCollision(co, newPos, &timestepFrac, &collisionForce)) {
			float timestepSegment = timestepFrac * timestepRemain;

			//----------------- Update potential position ---------------------
			newPos = pos + velocity * timestepSegment;

			//------------------- Create collision force ----------------------------
			Vector3D vc = velocity + newAccel * timestep;
			
			Vector3D vn = normal * vc.dotProduct(normal);
			Vector3D vt = vc - vn;
			Vector3D vnPrime = vn * -elasticity;
			Vector3D vtPrime = vt * (1 - friction); // TODO: implement more accurate model

			newVel = vnPrime + vtPrime;

			*collisionForce += ;

			//--------------- Update remaining timestep -----------------
			timestepRemain -= timestepSegment;
		}
		//-------------- If no collision -------------------------
		else {
			timestepRemain = 0;
		}

		//-------------- Update the current time ---------------------
		cTime = currentTime - timestepRemain; // update current time

		//-------------- Get the forces at this time and calc the acceleration ----------
		size_t fSize = forces.size();
		size_t aSize = accels.size();

		Vector3D netAccel = collisionForce;
		// calculate net acceleration
		for(int i=0; i<fSize; i++) {
			netAccel += forces[i].get(cTime, this);
		}
		netAccel = netAccel/mass;
		for(int i=0; i<aSize; i++) {
			netAccel += accels[i].get(cTime, this);
		}

		//------------- Update the velocity and the position for this time -----------
		velocity += newAccel * timestepRemain;
		pos = newPos;
	}
}

// Check if there is a collision with other ColliderObjects. Returns true if there is a collision
// and also returns the timestep fraction at which the collision occurred along with the collision
// force that would be applied to this RigidBody
bool RigidBody::earliestCollision(const std::vector<ColliderObject>& co, const Vector3D& newPos,
                                  float *timestepFrac, Vector3D* collisionForce) const 
{
	*timestepFrac = 1.0f;
	size_t collObjSize = co.size();

	float possibleTimestepFrac;
	Vector3D possibleCollisionForce;
	// For each colliderObject
	for(int k=0; k<collObjSize; k++) {
		
		// Check if current rigidbody collided with a colliderObject while
		// moving to its newPos
		if(collision(co[k], &possibleTimestepFrac, &possibleCollisionForce)) {
			if( possibleTimestepFrac < *timestepFrac ) {
				*timestepFrac = possibleTimestepFrac;
				*collisionForce = possibleCollisionForce;
			}
		}
	}

	// If we collided with something
	if(*timestepFrac < 1.0f) return true;

	return false;
}

bool RigidBody::collision(const ColliderObject& o, const Vector3D& newPos, float *timestepFrac,
			   Vector3D* collisionForce) const
{
}


void RigidBody::calcNewState(const Vector3D& acceleration, const Vector3D& force,
                             float timestep) {
	// Calculate acceleration
	Vector3D newAccel = acceleration + force/mass;
	
	// Compute new velocity
	newVel = velocity + newAccel * timestep;
	
	// Compute new pos.
	newPos = pos + newVel * timestep;
}

void RigidBody::calcNewState(const Vector3D& acceleration, const Vector3D& force,
				float timestep, const Vector3D& normal) {
	// Calculate acceleration
	Vector3D newAccel = acceleration + force/mass;
	
	Vector3D vc = pos + newAccel * timestep;
	Vector3D xc = pos + velocity * timestep;
	
	Vector3D vn = normal * vc.dotProduct(normal);
	Vector3D vt = vc - vn;
	Vector3D vnPrime = vn * -elasticity;
	Vector3D vtPrime = vt * (1 - friction); // TODO: implement more accurate model

	newVel = vnPrime + vtPrime;
	newPos = xc;
}


*/
