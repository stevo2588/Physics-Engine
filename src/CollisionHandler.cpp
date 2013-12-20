#include <CollisionHandler.h>

#include <Shape.h>
#include <QuadPlane.h>
#include <Sphere.h>
#include <Utility.h>

#include <cmath>

// TODO LATER: Lots to do here
	
//****************************************************************************************
//--------------------------- COLLISION METHODS FOR SHAPES -------------------------------
//****************************************************************************************

//--------------------------- SHAPE AND SHAPE (only needed to satisfy compiler) ----------
bool CollisionHandler::collision(const Shape& qp, const Shape& qpUpdated,
			                     const Shape& s, const Shape& sUpdated,
			                     float &timestepFrac, Vector3D &collisionNormal)
{
	return false;
}


//--------------------------- QUADPLANE AND SPHERE ---------------------------------------
bool CollisionHandler::collision(const QuadPlane& qp, const QuadPlane& qpUpdated,
			                     const Sphere& s, const Sphere& sUpdated,
			                     float &timestepFrac, Vector3D &collisionNormal)
{
	// NOTES:
	// -Assumes there are no collisions at p0
	// -Assumes p0 and p1 are relative to the plane position
	//
	// -------------------------------------------------------------
	// BREAKDOWN:
	// -------------------------------------------------------------
	//
	// get vector from point on plane to first sphere position
	// planeToSphere = p0 - pos;
	//
	// get signed length of projection planeToSphere against normal
	// D0 = planeToSphere.dotProduct(normal)
	//
	// do the same for final sphere position
	// D1 = (p1 - pos).dotProduct(normal)
	//
	// We need to take radius into account so we check whether D1 is + or - and modify
	// D1 appropriately:
	// if(D1 < 0) D1 += r
	// else D1 -= r
	//
	// Check if the signs of D0 and D1 are different
	// if(D0 * D1 < 0)
	// If they are not different there is no collision, but if they are we calculate the
	// timestep fraction:
	// timestepFrac = abs(D0/(D1-D0))
	// 
	// Calculate the plane collision position (TODO: this is just linear interpolation
	// and doesn't take into account if rate of acceleration is non-linear)
	// collisionPos = p0 + (timestepFrac * (p1 - p0))
	// 
	// Check if the collision position is within the quad:
	// TODO
	
	// TODO NOW
	// Transform Sphere into plane space
	//s.transform.applyTransform(qp.transform.getInverse());
	PBTransform sTrans = qp.transform.transformOther(s.transform);
	PBTransform sUpTrans = qp.transform.transformOther(sUpdated.transform);
	
	float D0 = (sTrans.getPos() - qp.transform.getPos()).dotProduct(qp.getNorm());
	float D1 = (sUpTrans.getPos() - qpUpdated.transform.getPos()).dotProduct(qp.getNorm());
	
	if(D1 < 0) D1 += s.getRad();
	else D1 -= s.getRad();

	if((D0 * D1) > 0) return false;

	timestepFrac = std::abs(D0/(D1-D0));
	collisionNormal = qp.getNorm();
	return true;
	
	/*
	float diff1 = p0.elements[i/2] - planePos[i];
	float diff2 = p1.elements[i/2] - planePos[i];
	if((diff1 * diff2) < 0) {
		*t = diff1/diff2;
		*n = norms[i];
		return true;
	}

	return false;
	*/

}
// ^ Flipped
bool CollisionHandler::collision(const Sphere& s, const Sphere& sUpdated,
			                     const QuadPlane& qp, const QuadPlane& qpUpdated,
			                     float &timestepFrac, Vector3D &collisionNormal)
{
	return collision(qp, qpUpdated, s, sUpdated, timestepFrac, collisionNormal);
}


// TODO LATER
//------------------ SPHERE AND SPHERE COLLISION ---------------------------------------
bool CollisionHandler::collision(const Sphere& s0, const Sphere& s0updated,
	                             const Sphere& s1, const Sphere& s1updated,
	                             float &timestepFrac, Vector3D &collisionNormal)
{
	return false;
}


// TODO LATER
//------------------ QUADPLANE AND QUADPLANE COLLISION ---------------------------------------
bool CollisionHandler::collision(const QuadPlane& qp0, const QuadPlane& qp0updated,
	                             const QuadPlane& qp1, const QuadPlane& qp1updated,
	                             float &timestepFrac, Vector3D &collisionNormal)
{
	return false;
}


