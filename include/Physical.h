#ifndef PHYSICAL_H
#define PHYSICAL_H

#include <memory>
#include <vector>
#include <functional>
#include <CollidableObject.h>
#include <Force.h>
#include <PhysicallyBased.h>

// A Physical object is affected by Forces
class Physical : public CollidableObject {
public:
	typedef std::unique_ptr<Physical> PhysPtr;
	typedef std::unique_ptr<CollidableObject> CollObjPtr;
	typedef std::unique_ptr<Force> ForcePtr;
	typedef std::reference_wrapper<const Force> ForceRef;

	// Update this Physical
	void update(const PBTime& theTime,
	            const std::vector<ForceRef>& forces, const std::vector<ForceRef>& accels)
	{
		update(theTime, *this, forces, accels);
	}

	// Get an updated version of this object (without actually updating)
	PhysPtr getUpdated(const PBTime& theTime,
	                   const std::vector<ForceRef>& forces, const std::vector<ForceRef>& accels)
	{
		PhysPtr updated = clonePhys();
		update(theTime, *updated, forces, accels);
		return updated;
	}

	virtual
	ForcePtr getCollisionForce(float timestep, float timestepFrac,
	                           const CollidableObject& updated, const Vector3D& normal) const=0;

protected:
	Physical(Shape& collider) : CollidableObject(collider) {}

	// This update function comes from the CollidableObject parent class. Won't need to be used
	// unless you want use the Physical as a CollidableObject, so we leave it virtual with a
	// blank definition.
	virtual void update(const PBTime& theTime, CollidableObject& co) {}

	// Function updates given Physical with the given forces
	virtual void update(const PBTime& theTime, Physical& p,
	                    const std::vector<ForceRef>& forces, const std::vector<ForceRef>& accels)=0;


	virtual CollObjPtr clone() const=0;

	virtual PhysPtr clonePhys() const=0;
};


#endif // PHYSICAL_H

