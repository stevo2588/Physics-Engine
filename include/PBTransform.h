#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Utility.h>

class PBTransform {
public:
	PBTransform()
	: transform(Matrix3D())/*, recentInverse(Matrix3D()), isInverseCurrent(true)*/
	{}

	PBTransform(double x, double y, double z)
	: transform(Matrix3D(x,y,z))
	{
		//transform.getInversion(recentInverse);
		//isInverseCurrent = true;
	}

	PBTransform(const Matrix3D& m) : transform(m) {
		//transform.getInversion(recentInverse);
		//isInverseCurrent = true;
	}

	Vector3D getPos() const {
		return Vector3D(transform.elements[0][3],
	                    transform.elements[1][3],
	                    transform.elements[2][3]);
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

	void translate(double x, double y, double z) {
		Matrix3D transMat(x, y, z);
		transform = transform * transMat;

		//isInverseCurrent = false;
	}

	void translate(const Vector3D& v) {
		translate(v.elements[0], v.elements[1], v.elements[2]);
	}

	// TODO LATER
	void rotate(double x, double y, double z) {
		//isInverseCurrent = false;
	}

	// TODO LATER
	void scale(double x, double y, double z) {
		//isInverseCurrent = false;
	}

	void applyTransform(const PBTransform& t) {
		transform = transform * t.transform;

		//isInverseCurrent = false;
	}

	friend class Renderable;

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

	//Matrix3D recentInverse;
	//bool isInverseCurrent;
};

#endif // TRANSFORM_H

