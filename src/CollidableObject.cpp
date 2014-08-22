
#include <CollidableObject.h>

#include <Force.h>

void CollidableObject::update(const PBTime& theTime) {
	update(theTime, *this);
}

CollidableObject::CollObjPtr CollidableObject::getUpdated(const PBTime& theTime) {
	CollObjPtr updated = clone();
	update(theTime, *updated);

	return updated;
}


bool CollidableObject::collisionCheck(float timestep, const CollidableObject& thisUpdated,
					     const CollidableObject& other, const CollidableObject& otherUpdated,
					     float& timestepFrac, ForcePtr& thisCollForce, ForcePtr& otherCollForce)
{
	Vector3D collisionNormal;

	if( collider.get().collision( thisUpdated.collider.get(), other.collider.get(),
	                              otherUpdated.collider.get(), timestepFrac, collisionNormal ))
	{
		thisCollForce = this->getCollisionForce(timestep, timestepFrac, thisUpdated, collisionNormal);
		otherCollForce = other.getCollisionForce(timestep, timestepFrac, otherUpdated, -collisionNormal);

		// If a force is NULL, that force will be equal and opposite the other force
		if( thisCollForce == NULL ) {
			thisCollForce = otherCollForce->clone();
			thisCollForce->flip();
		}
		else if( otherCollForce == NULL) {
			otherCollForce = thisCollForce->clone();
			otherCollForce->flip();
		}

		return true;
	}

	return false;

	// OLD
	/*
	// get rb2 transform in rb1 space
	PBTransform rb2_trans = rb1.transformOther(rb2.transform);

	for(int i=0; i<colliderSize; i++) {
		Vector3D collWorldTrans = rb1.transformChild(rb1.colliders[i].transform);
		// TODO NOW: get new transform
		Vector3D collWorldNewTrans = rb1.transformChild(rb1.colliders[i].transform);
		int colliderSize2 = o.getColliderCount();
		for(int j=0; j<colliderSize2; j++) {
			Vector3D otherCollWorldTrans = o.getPos() + o.getCollider(j)->getPos();
			// NOTE: change positions to be relative to the other object's collider position
			Vector3D p0 = collWorldTrans - otherCollWorldTrans;
			Vector3D p1 = collWorldNewTrans - otherCollWorldTrans;
			if( colliders[i]->collision( p0, p1, *(o.getCollider(j)),
										 timestepFrac, collisionNormal) )
			{
				// TODO LATER: currently returns info for the very first collision we find.
				// Should it check for anymore?

				// TODO NOW
				DeferredForce* df1 = rb1.getCollisionForce(collisionNormal);
				DeferredForce* df2 = rb2.getCollisionForce();
				collisionForce.set(df1, df2);

				return true;
			}
		}
	}
	return false;
	*/

	// OLDER
	//return other.collisionWith(otherUpdated, *this, thisUpdated, timestepFrac, collisionForce);
}

