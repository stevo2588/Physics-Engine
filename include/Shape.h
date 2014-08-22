//-------------------------------------------------
//------------- SHAPE.H --------------------------
//-------------------------------------------------
#ifndef SHAPE_H
#define SHAPE_H

#include <TComponent.h>
#include <Renderable.h>
#include <Utility.h>
#include <CollisionHandler.h>
#include <PBTransform.h>

class Shape : public TComponent, public Renderable {
public:
	virtual ~Shape() {}

	// Check if this shape has collided with another Shape between 2 positions.
	// Return fraction of timestep and normal of the other object's collision point
	bool collision(const Shape& thisUpdated,
	                       const Shape& other, const Shape& otherUpdated,
	                       float& timestepFrac, Vector3D& collisionNormal) const
	{
		if(other.collideWith(otherUpdated, convert(*this), convert(thisUpdated),
		                     timestepFrac, collisionNormal))
		{
			return true;
		}

		return false;
	}

	template <typename T>
	bool collideWith(const Shape& thisUpdated,
	                 const T& other, const T& otherUpdated,
	                 float& timestepFrac, Vector3D& collisionNormal) const
	{
		if(CollisionHandler::collision(other, otherUpdated, *this, this->convert(thisUpdated),
		                               timestepFrac, collisionNormal))
		{
			return true;
		}

		return false;
	}

	// This pure virtual method should convert a const Shape& to the derived class
	virtual const Shape& convert(const Shape& s) const=0;

	template <typename T1, typename T2>
	friend bool CollisionHandler::collision(const T1& s1, const T1& s1_potential,
	                                        const T2& s2, const T2& s2_potential,
	                                        float& timestepFrac, Vector3D& collisionNormal);

	virtual void openGLDraw() const=0;

protected:
	Shape() {}
};


#endif // SHAPE_H

