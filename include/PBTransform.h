#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Utility.h>
#include <ostream>

class PBTransform {
public:
	//typedef std::reference_wrapper<PBTransform> TransformRef;

	//PBTransform(PBTransform& parent)
	//: transform(Matrix3D()), parent()/*, recentInverse(Matrix3D()), isInverseCurrent(true)*/
	//{}
	PBTransform();
	PBTransform(float x, float y, float z);
	PBTransform(const Matrix3D& m);

	Vector3D getPos() const {
		return Vector3D(transform.getElement(0,3),
	                    transform.getElement(1,3),
	                    transform.getElement(2,3));
	}

	const Matrix3D& getTransform() const {
		return transform;
	}

	// Takes a sibling transform and changes it into this transform's space
	PBTransform transformOther(const PBTransform& t) const {
		return PBTransform(getMatrixInversion() * t.transform);
	}

	// Takes a child transform and transforms it into this space
	PBTransform transformChild(const PBTransform& t) const {
		return PBTransform(transform * t.transform);
	}

	void translate(float x, float y, float z) {
		Matrix3D transMat(x, y, z);
		transform = transform * transMat;

		//isInverseCurrent = false;
	}

	void translate(const Vector3D& v) {
		translate(v.elements[0], v.elements[1], v.elements[2]);
	}

	// TODO LATER
	void rotate(float x, float y, float z) {
		//isInverseCurrent = false;
	}

	// TODO LATER
	void scale(float x, float y, float z) {
		//isInverseCurrent = false;
	}

	void applyTransform(const PBTransform& t) {
		transform = transform * t.transform;

		//isInverseCurrent = false;
	}


	// Hierarchical access
	//TransformRef getParent() { return parent; }
	//int getChildCount() const { return children.size(); }
	//TransformRef getChild(int i) { return children[i]; }

	friend class Renderable;

	friend std::ostream& operator<<(std::ostream& os, const PBTransform& pbt);

private:
	Matrix3D getMatrixInversion() const {
		//if(!isInverseCurrent) {
		//	transform.getInversion(recentInverse);
		//}
		//return recentInverse;
		Matrix3D inverse;
		transform.getInversion(inverse);
		return inverse;
	}


	Matrix3D transform;

	//TransformRef parent;
	//std::vector<TransformRef> children;

	//Matrix3D recentInverse;
	//bool isInverseCurrent;
};



class Object;

#include <functional>
#include <vector>

class PBObjectTransform : public PBTransform {
public:
	typedef std::reference_wrapper<const Object> ObjectRef;

	PBObjectTransform(float x, float y, float z, const Object& parentObject, const Object& o)
	: PBTransform(x,y,z), object(o), parentObject(parentObject) { }

	PBObjectTransform(const Matrix3D& m, const Object& parentObject, const Object& o)
	: PBTransform(m), object(o), parentObject(parentObject) { }

	// Hierarchical access
	ObjectRef getParentObject() { return parentObject; }
	int getChildObjectCount() const { return childObjects.size(); }
	ObjectRef getChildObject(int i) { return childObjects[i]; }


private:
	const Object& object;

	ObjectRef parentObject;
	std::vector<ObjectRef> childObjects;
};

#endif // TRANSFORM_H

