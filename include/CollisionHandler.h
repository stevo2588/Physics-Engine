#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

class Shape;
class QuadPlane;
class Sphere;
class PBTransform;
class Vector3D;

namespace CollisionHandler {
	
	//****************************************************************************************
	//--------------------------- COLLISION METHODS FOR SHAPES -------------------------------
	//****************************************************************************************
	
	//--------------------------- SHAPE AND SHAPE (only needed to satisfy compiler) ----------
	bool collision(const Shape& qp, const Shape& qpUpdated,
			       const Shape& s, const Shape& sUpdated,
			       float &timestepFrac, Vector3D &collisionNormal);

	//--------------------------- QUADPLANE AND SPHERE ---------------------------------------
	bool collision(const QuadPlane& qp, const QuadPlane& qpUpdated,
			       const Sphere& s, const Sphere& sUpdated,
			       float &timestepFrac, Vector3D &collisionNormal);

	// ^ Flipped
	bool collision(const Sphere& s, const Sphere& sUpdated,
			       const QuadPlane& qp, const QuadPlane& qpUpdated,
			       float &timestepFrac, Vector3D &collisionNormal);


	//------------------ SPHERE AND SPHERE COLLISION ---------------------------------------
	bool collision(const Sphere& s0, const Sphere& s0updated,
	               const Sphere& s1, const Sphere& s1updated,
	               float &timestepFrac, Vector3D &collisionNormal);


	//------------------ QUADPLANE AND QUADPLANE COLLISION ---------------------------------
	bool collision(const QuadPlane& qp0, const QuadPlane& qp0updated,
	               const QuadPlane& qp1, const QuadPlane& qp1updated,
	               float &timestepFrac, Vector3D &collisionNormal);
}


#endif // COLLISIONHANDLER_H

