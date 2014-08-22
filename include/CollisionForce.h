#ifndef COLLISIONFORCE
#define COLLISIONFORCE

#include <memory>
#include <DeferredForce.h>
#include <Force.h>

// CollisionForce is used to defer the evaluation of a collision force.
class CollisionForce {
public:
	CollisionForce()  {}
	virtual void ~CollisionForce() { }

	typedef std::unique_ptr<DeferredForce> DeferredForcePtr;
	typedef std::unique_ptr<Force> ForcePtr;

	void set(DeferredForcePtr a, DeferredForcePtr b) {
		this->a = std::move(a); this->b = std::move(b);
	}

	IndependentForce get(const PBTime& theTime) const {
		ForcePtr f1 = std::move(a->get(theTime.getTimestep()));
		ForcePtr f2 = std::move(b->get(theTime.getTimestep()));
		IndependentForce indForce(*f1 + *f2);

		return indForce;
	}

private:
	DeferredForcePtr a;
	DeferredForcePtr b;
};



#endif // COLLISIONFORCE
