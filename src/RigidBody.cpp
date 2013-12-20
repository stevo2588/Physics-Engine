
/*
#include <RigidBody.h>



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
