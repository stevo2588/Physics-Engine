#include <PBTransform.h>

PBTransform::PBTransform() : transform(Matrix3D(0,0,0)) {}

PBTransform::PBTransform(float x, float y, float z)
: transform(Matrix3D(x,y,z))
{
	//transform.getInversion(recentInverse);
	//isInverseCurrent = true;
}

PBTransform::PBTransform(const Matrix3D& m)
: transform(m) {
	//transform.getInversion(recentInverse);
	//isInverseCurrent = true;
}

std::ostream& operator<<(std::ostream& os, const PBTransform& pbt) {
	return os << pbt.getTransform();
}
