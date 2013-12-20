#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <functional>
#include <vector>
#include <PBTransform.h>

#include <memory>

class CollidableObject;
class Physical;
class ForceEnvironment;
class PBTime;
class Force;
class CollisionForce;

// Physicals and ColliderObjects can all interact with each other in the same Environment. The
// Environment also holds ForceEnvironments, which are sets of Forces that can be assigned to
// different Physicals.
//
// Responsibilities: An Environment is responsible for managing a set of ForceEnvironments,
// ColliderObjects, and Physicals. Management of these objects includes: telling Physicals what
// forces to apply at the current time, checking for collisions at the current time and telling
// the objects to act accordingly, and

class Environment {
public:
	Environment();
	Environment(const PBTransform& t);

	typedef std::reference_wrapper<CollidableObject> CollObjRef;
	typedef std::reference_wrapper<Physical> PhysicalRef;
	typedef std::reference_wrapper<ForceEnvironment> ForceEnvRef;
	typedef std::reference_wrapper<const Force> ForceRef;
	typedef std::unique_ptr<Force> ForcePtr;

	PBTransform transform;

	void addForceEnvironment(ForceEnvironment& fe);
	void addCollidable(CollidableObject& co);
	void addPhysical(Physical& ph);

	// link ForceEnvironment with a physical
	void linkForceEnv(unsigned int physical, unsigned int forceEnv);

	void update(const PBTime& theTime);

private:
	bool earliestCollision(const PBTime& theTime, float& timestepFrac,
                           unsigned int& objectAIndex, unsigned int& objectBIndex,
                           bool& bIsPhysical, ForcePtr& collForce0, ForcePtr& collForce1);

	void updateAllObjects(const PBTime& theTime);

	std::vector<CollObjRef> collidables;
	size_t collidableCount;

	std::vector<PhysicalRef> physicals;
	size_t physicalCount;

	// vector containing vectors of Force references which correspond to each physical.
	std::vector< std::vector<ForceRef> > physicalsForces;
	// vector containing vectors of Acceleration references which correspond to each physical.
	std::vector<std::vector<ForceRef> > physicalsAccels;

	// vector of force environments
	std::vector<ForceEnvRef> forceEnvs;
	size_t forceEnvCount;
};

#endif // ENVIRONMENT_H

