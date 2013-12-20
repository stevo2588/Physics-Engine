#include <Environment.h>

#include <PBTime.h>
#include <CollidableObject.h>
#include <Physical.h>
#include <Force.h>
#include <ForceEnvironment.h>
#include <PhysicallyBased.h>

#include <memory>

Environment::Environment() : collidableCount(0), physicalCount(0), forceEnvCount(0)
{
}

Environment::Environment(const PBTransform& t) : transform(t), collidableCount(0),
                                               physicalCount(0), forceEnvCount(0)
{
}

void Environment::addForceEnvironment(ForceEnvironment& fe) {
	forceEnvs.push_back( ForceEnvRef(fe) );
	forceEnvCount++;
}

void Environment::addCollidable(CollidableObject& co) {
	collidables.push_back( CollObjRef(co) );
	collidableCount++;
}

void Environment::addPhysical(Physical& ph) {
	physicals.push_back( PhysicalRef(ph) );
	physicalCount++;
}

// TODO LATER: update and unlink too?
void Environment::linkForceEnv(unsigned int physical, unsigned int forceEnv) {

	for( auto& i: forceEnvs[forceEnv].get().forces ) {
		physicalsForces[physical].push_back( i );
	}
	for( auto& i: forceEnvs[forceEnv].get().accels ) {
		physicalsAccels[physical].push_back( i );
	}
}


bool Environment::earliestCollision(const PBTime& theTime, float& timestepFrac,
                                    unsigned int& objectAIndex, unsigned int& objectBIndex,
                                    bool& bIsPhysical,
                                    ForcePtr& collForce0, ForcePtr& collForce1)
{
	// TODO LATER: should this also check for collisions between CollidableObjects?
	
	typedef std::unique_ptr<Physical> PhysPtr;
	typedef std::unique_ptr<CollidableObject> CollObjPtr;
	
	float timestep = theTime.getTimestep();
	float currentTime = theTime.getElapsedTime();

	timestepFrac = 1.0f;

	objectAIndex = -1;
	objectBIndex = -1;

	// for each Physical
	for(int i=0; i<physicalCount; i++) {

		float curTimestepFrac;
		ForcePtr cf0;
		ForcePtr cf1;

		// Get potential state of the current physical
		PhysPtr physUpdated = physicals[i].get().getUpdated(theTime, physicalsForces[i],
		                                                    physicalsAccels[i]);
		// check against CollidableObjects
		for(int j=0; j<collidableCount; j++) {

			CollObjPtr collUpdated = collidables[j].get().getUpdated(theTime);

			if(physicals[i].get().collisionCheck(timestep, (CollidableObject&)(*physUpdated),
			                                     collidables[j].get(), *collUpdated,
			                                     curTimestepFrac, cf0, cf1))
			{
				if( curTimestepFrac < timestepFrac ) {
					timestepFrac = curTimestepFrac;
					objectAIndex = i;
					objectBIndex = j;
					bIsPhysical = false;
					collForce0 = std::move(cf0);
					collForce1 = std::move(cf1);
				}
			}
		}

		// check against other Physicals
		for(int j=0, checkCount=i-1; j<checkCount; j++) {

			PhysPtr phys2Updated = physicals[i].get().getUpdated(theTime, physicalsForces[j],
			                                                     physicalsAccels[j]);

			if(physicals[i].get().collisionCheck(timestep, (CollidableObject&)(*physUpdated),
			                                     physicals[checkCount].get(),
			                                     (CollidableObject&)(*phys2Updated),
			                                     curTimestepFrac, cf0, cf1))
			{
				if( curTimestepFrac < timestepFrac ) {
					timestepFrac = curTimestepFrac;
					objectAIndex = i;
					objectBIndex = checkCount;
					bIsPhysical = true;
					collForce0 = std::move(cf0);
					collForce1 = std::move(cf1);
				}
			}
		}
	}

	// If a collision was found
	if(objectAIndex != -1) return true;

	return false;

}

// Update every object by the timestep. 
void Environment::updateAllObjects(const PBTime& theTime)
{
	for(int i=0; i<physicalCount; i++) {
		physicals[i].get().update(theTime, physicalsForces[i], physicalsAccels[i]);
	}
	for(int i=0; i<collidableCount; i++) {
		collidables[i].get().update(theTime);
	}
}

void Environment::update(const PBTime& theTime) {
	float timestep = theTime.getTimestep();
	float currentTime = theTime.getElapsedTime();

	float timestepRemain = timestep;
	float timestepFrac = 1.0f;
	float cTime = currentTime - timestep;
	unsigned int objectAIndex, objectBIndex;
	bool bIsPhysical;
	ForcePtr collisionForce0;
	ForcePtr collisionForce1;


	while(timestepRemain > 0) {
		float deltaTime;
		
		// find timestepFraction of the earliest collision between all objects
		if(earliestCollision( PBTime(timestepRemain, cTime), timestepFrac,
		                      objectAIndex, objectBIndex,
		                      bIsPhysical, collisionForce0, collisionForce1 ))
		{
			// update deltaTime
			deltaTime = timestepRemain * timestepFrac;
			
			// update timestepRemain
			timestepRemain -= deltaTime;

			cTime = currentTime - timestepRemain;

			// add collision force to the forces of the correct objects
			physicalsForces[objectAIndex].push_back( ForceRef( *collisionForce0 ) );
			if(bIsPhysical)
				physicalsForces[objectBIndex].push_back( ForceRef( *collisionForce1 ) );
			
			// TODO LATER: notify Collidables of a collision someway?

			updateAllObjects( PBTime(deltaTime, cTime) );

			// remove collision force now that objects have been updated
			physicalsForces[objectAIndex].pop_back();
			if(bIsPhysical)
				physicalsForces[objectBIndex].pop_back();
		}

		// no collision
		else {
			deltaTime = timestepRemain;
			timestepRemain = 0;

			cTime = currentTime - timestepRemain;

			updateAllObjects(PBTime(deltaTime, cTime));
		}
	}
}

