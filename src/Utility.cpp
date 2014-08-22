//-------------------------------------------------
//------------- UTILITY.CPP -----------------------
//-------------------------------------------------
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <Utility.h>

//------------------------------------------------------------------------------------------
//---------------------------------------- Vector3D ----------------------------------------
//------------------------------------------------------------------------------------------
Vector3D::Vector3D() {
	elements[0] = 0;
	elements[1] = 0;
	elements[2] = 0;
}

Vector3D::Vector3D(float x, float y, float z) {
	elements[0] = x;
	elements[1] = y;
	elements[2] = z;
}

float Vector3D::calcMagnitude() const {
   return sqrt(elements[0]*elements[0]+elements[1]*elements[1]+elements[2]*elements[2]);
}

Vector3D Vector3D::normalize() const {
   float mag = calcMagnitude();
   return Vector3D(elements[0]/mag,elements[1]/mag,elements[2]/mag);
}

float Vector3D::dotProduct(const Vector3D &v) const {
	float prod = this->elements[0]*v.elements[0] + this->elements[1]*v.elements[1] + this->elements[2]*v.elements[2];
	return prod;
}

Vector3D Vector3D::crossProduct(const Vector3D &v) {
   Vector3D prod = Vector3D(elements[1]*v.elements[2] - v.elements[1]*elements[2],
                   elements[2]*v.elements[0] - v.elements[2]*elements[0],
                   elements[0]*v.elements[1] - v.elements[0]*elements[1]);
   return prod;
}

Vector3D& Vector3D::operator=(const Vector3D &rhs) {
	if(this != &rhs) {
		// Deallocate, allocate new space, copy values
		this->elements[0] = rhs.elements[0];
		this->elements[1] = rhs.elements[1];
		this->elements[2] = rhs.elements[2];
	}
	return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D &rhs) {
	this->elements[0] += rhs.elements[0];
	this->elements[1] += rhs.elements[1];
	this->elements[2] += rhs.elements[2];

	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D &rhs) {
	this->elements[0] -= rhs.elements[0];
	this->elements[1] -= rhs.elements[1];
	this->elements[2] -= rhs.elements[2];

	return *this;
}

Vector3D Vector3D::operator-() const {
   Vector3D v(-elements[0],-elements[1],-elements[2]);
   return v;
}

Vector3D operator+(const Vector3D &v1, const Vector3D &v2) {
	return Vector3D(v1.elements[0]+v2.elements[0],
	                v1.elements[1]+v2.elements[1],
	                v1.elements[2]+v2.elements[2]);
}

Vector3D operator-(const Vector3D &v1, const Vector3D &v2) {
	return Vector3D(v1.elements[0]-v2.elements[0],
	                v1.elements[1]-v2.elements[1],
	                v1.elements[2]-v2.elements[2]);
}

float operator*(const Vector3D &v1, const Vector3D &v2) {
	return v1.elements[0]*v2.elements[0] +
	       v1.elements[1]*v2.elements[1] +
	       v1.elements[2]*v2.elements[2];
}

Vector3D operator*(const Vector3D &v1, const float s) {
   return Vector3D(v1.elements[0]*s,v1.elements[1]*s,v1.elements[2]*s);
}

Vector3D operator/(const Vector3D &v1, const float s) {
   try {
      return Vector3D(v1.elements[0]/s,v1.elements[1]/s,v1.elements[2]/s);
   }
   catch(const std::logic_error &) {
      std::cerr << "Division by 0" << std::endl;
   }

   return Vector3D(0, 0, 0);
}

Vector3D operator*(const Matrix3D &s, const Vector3D &v) { // technically post-multiplication
	//std::cout << "Matrix x Vector" << std::endl;
	Vector3D prod(0,0,0);

	prod.elements[0] = s.getElement(0,0)*v.elements[0] + s.getElement(0,1)*v.elements[1] +
	                   s.getElement(0,2)*v.elements[2] + s.getElement(0,3);
	prod.elements[1] = s.getElement(1,0)*v.elements[0] + s.getElement(1,1)*v.elements[1] +
	                   s.getElement(1,2)*v.elements[2] + s.getElement(1,3);
	prod.elements[2] = s.getElement(2,0)*v.elements[0] + s.getElement(2,1)*v.elements[1] +
	                   s.getElement(2,2)*v.elements[2] + s.getElement(2,3);

	return prod;
}

// no translation, for use with direction vectors
Vector3D m_mult_dirVec(const Matrix3D &s, const Vector3D &v) {
	Vector3D prod(0,0,0);

	prod.elements[0] = s.getElement(0,0)*v.elements[0] + s.getElement(0,1)*v.elements[1] +
	                   s.getElement(0,2)*v.elements[2];
	prod.elements[1] = s.getElement(1,0)*v.elements[0] + s.getElement(1,1)*v.elements[1] +
	                   s.getElement(1,2)*v.elements[2];
	prod.elements[2] = s.getElement(2,0)*v.elements[0] + s.getElement(2,1)*v.elements[1] +
	                   s.getElement(2,2)*v.elements[2];

	return prod;
}

std::ostream& operator<< (std::ostream &os, const Vector3D& vec) {
	os << "(" << vec.elements[0] << "," << vec.elements[1] << "," << vec.elements[2] << ")";
	return os;
}


//------------------------------------------------------------------------------------------
//---------------------------------------- Vector2D ----------------------------------------
//------------------------------------------------------------------------------------------
std::ostream& operator<< (std::ostream &os, const Vector2D& vec) {
	os << "(" << vec.elements[0] << "," << vec.elements[1] << ")";
	return os;
}


//------------------------------------------------------------------------------------------
//---------------------------------------- Matrix3D ----------------------------------------
//------------------------------------------------------------------------------------------
//---------- A Specialized 4 x 4 matrix class for use with 3D transformations. -------------
//------------------------------------------------------------------------------------------

Matrix3D::Matrix3D() {
	setIDMat();
}

// Creates a matrix with all values initialized to 0. nullptr_t is just a dummy arg
Matrix3D::Matrix3D(nullptr_t n) {
	getElementRef(0,0) = 0; getElementRef(0,1) = 0; getElementRef(0,2) = 0; getElementRef(0,3) = 0;
	getElementRef(1,0) = 0; getElementRef(1,1) = 0; getElementRef(1,2) = 0; getElementRef(1,3) = 0;
	getElementRef(2,0) = 0; getElementRef(2,1) = 0; getElementRef(2,2) = 0; getElementRef(2,3) = 0;
	getElementRef(3,0) = 0; getElementRef(3,1) = 0; getElementRef(3,2) = 0; getElementRef(3,3) = 1;
}

/*
Matrix3D::Matrix3D(float elem[rowSize][columnSize]) {
	for(int i=0; i<rowSizeMinus1; ++i)
		for(int j=0; j<columnSize; ++j)
			elements[i][j] = elem[i][j];
}
*/

/*
Matrix3D::Matrix3D(float x, float y, float z) {
	elements[0][0] = 1; elements[0][1] = 0; elements[0][2] = 0; elements[0][3] = x;
	elements[1][0] = 0; elements[1][1] = 1; elements[1][2] = 0; elements[1][3] = y;
	elements[2][0] = 0; elements[2][1] = 0; elements[2][2] = 1; elements[2][3] = z;
}
*/
Matrix3D::Matrix3D(float x, float y, float z) {
	getElementRef(0,0) = 1; getElementRef(0,1) = 0; getElementRef(0,2) = 0; getElementRef(0,3) = x;
	getElementRef(1,0) = 0; getElementRef(1,1) = 1; getElementRef(1,2) = 0; getElementRef(1,3) = y;
	getElementRef(2,0) = 0; getElementRef(2,1) = 0; getElementRef(2,2) = 1; getElementRef(2,3) = z;
	getElementRef(3,0) = 0; getElementRef(3,1) = 0; getElementRef(3,2) = 0; getElementRef(3,3) = 1;
}

/*
void Matrix3D::setIDMat() {
	elements[0][0] = 1; elements[0][1] = 0; elements[0][2] = 0; elements[0][3] = 0;
	elements[1][0] = 0; elements[1][1] = 1; elements[1][2] = 0; elements[1][3] = 0;
	elements[2][0] = 0; elements[2][1] = 0; elements[2][2] = 1; elements[2][3] = 0;
}
*/
void Matrix3D::setIDMat() {
	getElementRef(0,0) = 1; getElementRef(0,1) = 0; getElementRef(0,2) = 0; getElementRef(0,3) = 0;
	getElementRef(1,0) = 0; getElementRef(1,1) = 1; getElementRef(1,2) = 0; getElementRef(1,3) = 0;
	getElementRef(2,0) = 0; getElementRef(2,1) = 0; getElementRef(2,2) = 1; getElementRef(2,3) = 0;
	getElementRef(3,0) = 0; getElementRef(3,1) = 0; getElementRef(3,2) = 0; getElementRef(3,3) = 1;
}

/*
bool Matrix3D::getInversion(Matrix3D &invOut) const {
	Matrix3D inv;
	float det;

    inv.elements[0][0] = elements[1][1]  * elements[2][2] +
	                     elements[2][1]  * elements[1][2];

    inv.elements[1][0] = -elements[1][0]  * elements[2][2] +
	                     elements[2][0] * elements[1][2];

    inv.elements[2][0] = elements[1][0]  * elements[2][1] +
	                     elements[2][0]  * elements[1][1];

    inv.elements[0][1] = -elements[0][1]  * elements[2][2] +
	                     elements[2][1]  * elements[0][2];

    inv.elements[1][1] = elements[0][0]  * elements[2][2] +
	                     elements[2][0]  * elements[0][2];

    inv.elements[2][1] = -elements[0][0]  * elements[2][1] +
	                     elements[2][0]  * elements[0][1];

    inv.elements[0][2] = elements[0][1]  * elements[1][2] +
	                     elements[1][1]  * elements[0][2];

    inv.elements[1][2] = -elements[0][0] * elements[1][2] +
	                     elements[1][0] * elements[0][2];

    inv.elements[2][2] = elements[0][0] * elements[1][1] +
	                     elements[1][0] * elements[0][1];

    inv.elements[0][3] = -elements[0][1] * elements[1][2] * elements[2][3] +
              elements[0][1] * elements[1][3] * elements[2][2] +
              elements[1][1] * elements[0][2] * elements[2][3] -
              elements[1][1] * elements[0][3] * elements[2][2] -
              elements[2][1] * elements[0][2] * elements[1][3] +
              elements[2][1] * elements[0][3] * elements[1][2];

    inv.elements[1][3] = elements[0][0] * elements[1][2] * elements[2][3] -
             elements[0][0] * elements[1][3] * elements[2][2] -
             elements[1][0] * elements[0][2] * elements[2][3] +
             elements[1][0] * elements[0][3] * elements[2][2] +
             elements[2][0] * elements[0][2] * elements[1][3] -
             elements[2][0] * elements[0][3] * elements[1][2];

    inv.elements[2][3] = -elements[0][0] * elements[1][1] * elements[2][3] +
               elements[0][0] * elements[1][3] * elements[2][1] +
               elements[1][0] * elements[0][1] * elements[2][3] -
               elements[1][0] * elements[0][3] * elements[2][1] -
               elements[2][0] * elements[0][1] * elements[1][3] +
               elements[2][0] * elements[0][3] * elements[1][1];

    det = elements[0][0] * inv.elements[0][0] + elements[0][1] * inv.elements[1][0] +
	      elements[0][2] * inv.elements[2][0];

    if (det == 0) return false;

    det = 1.0 / det;

    for(int i=0; i<rowSizeMinus1; i++)
		for(int j=0; j<columnSize; j++)
			invOut.elements[i][j] = inv.elements[i][j] * det;

    return true;
}
*/
bool Matrix3D::getInversion(Matrix3D &invOut) const {
	Matrix3D inv;
	float det;

    inv.getElementRef(0,0) = getElement(1,1)  * getElement(2,2) +
	                         getElement(2,1) * getElement(1,2);

    inv.getElementRef(1,0) = -getElement(1,0) * getElement(2,2) +
	                         getElement(2,0) * getElement(1,2);

    inv.getElementRef(2,0) = getElement(1,0) * getElement(2,1) +
	                         getElement(2,0) * getElement(1,1);

    inv.getElementRef(0,1) = -getElement(0,1) * getElement(2,2) +
	                         getElement(2,1) * getElement(0,2);

    inv.getElementRef(1,1) = getElement(0,0) * getElement(2,2) +
	                         getElement(2,0) * getElement(0,2);

    inv.getElementRef(2,1) = -getElement(0,0) * getElement(2,1) +
	                         getElement(2,0) * getElement(0,1);

    inv.getElementRef(0,2) = getElement(0,1) * getElement(1,2) +
	                         getElement(1,1) * getElement(0,2);

    inv.getElementRef(1,2) = -getElement(0,0) * getElement(1,2) +
	                         getElement(1,0) * getElement(0,2);

    inv.getElementRef(2,2) = getElement(0,0) * getElement(1,1) +
	                         getElement(1,0) * getElement(0,1);

    inv.getElementRef(0,3) = -getElement(0,1) * getElement(1,2) * getElement(2,3) +
                             getElement(0,1) * getElement(1,3) * getElement(2,2) +
                             getElement(1,1) * getElement(0,2) * getElement(2,3) -
                             getElement(1,1) * getElement(0,3) * getElement(2,2) -
                             getElement(2,1) * getElement(0,2) * getElement(1,3) +
                             getElement(2,1) * getElement(0,3) * getElement(1,2);

    inv.getElementRef(1,3) = getElement(0,0) * getElement(1,2) * getElement(2,3) -
                             getElement(0,0) * getElement(1,3) * getElement(2,2) -
                             getElement(1,0) * getElement(0,2) * getElement(2,3) +
                             getElement(1,0) * getElement(0,3) * getElement(2,2) +
                             getElement(2,0) * getElement(0,2) * getElement(1,3) -
                             getElement(2,0) * getElement(0,3) * getElement(1,2);

    inv.getElementRef(2,3) = -getElement(0,0) * getElement(1,1) * getElement(2,3) +
                             getElement(0,0) * getElement(1,3) * getElement(2,1) +
                             getElement(1,0) * getElement(0,1) * getElement(2,3) -
                             getElement(1,0) * getElement(0,3) * getElement(2,1) -
                             getElement(2,0) * getElement(0,1) * getElement(1,3) +
                             getElement(2,0) * getElement(0,3) * getElement(1,1);

    det = getElement(0,0) * inv.getElement(0,0) + getElement(0,1) * inv.getElement(1,0) +
	      getElement(0,2) * inv.getElement(2,0);

    if (det == 0) return false;

    det = 1.0 / det;

    for(int i=0; i<rowSizeMinus1; i++)
		for(int j=0; j<columnSize; j++)
			invOut.getElementRef(i,j) = inv.getElement(i,j) * det;

    return true;
}

/*
Matrix3D& Matrix3D::operator=(const Matrix3D &rhs) {
	if(this != &rhs) {
		// Deallocate, allocate new space, copy values
		for(int i=0; i<rowSizeMinus1; ++i)
			for(int j=0; j<columnSize; ++j)
				elements[i][j] = rhs.getElem(i,j);
	}
	return *this;
}
*/
Matrix3D& Matrix3D::operator=(const Matrix3D &rhs) {
	elements = rhs.elements;
}

// Specialized for 3D Transformations (acts as if all matrices have a 4th row with [0 0 0 1])
/*
Matrix3D operator*(const Matrix3D &s1, const Matrix3D &s2) {
	Matrix3D prod;
	for(int k=0; k<rowSizeMinus1; ++k) {
		for(int i=0; i<3; ++i) {
			for(int j=0; j<3; ++j)
				prod.elements[k][i] += s1.elements[j][i] * s2.elements[k][j];
		}
	}
	for(int i=0; i<rowSizeMinus1; i++) {
		prod.elements[i][3] =
		s1.elements[i][0] * s2.elements[0][3] +
		s1.elements[i][1] * s2.elements[1][3] +
		s1.elements[i][2] * s2.elements[2][3] +
		s1.elements[i][3];
	}
	return prod;
}
*/
Matrix3D operator*(const Matrix3D &s1, const Matrix3D &s2) {
	Matrix3D prod(NULL);

	for(int k=0; k<Matrix3D::rowSizeMinus1; k++) {
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++)
				prod.getElementRef(k,i) += s1.getElement(j,i) * s2.getElement(k,j);
		}
	}
	for(int i=0; i<Matrix3D::rowSizeMinus1; i++) {
		prod.getElementRef(i,3) = s1.getElement(i,0) * s2.getElement(0,3) +
		                          s1.getElement(i,1) * s2.getElement(1,3) +
		                          s1.getElement(i,2) * s2.getElement(2,3) +
		                          s1.getElement(i,3);
	}
	return prod;
}

std::ostream& operator<<(std::ostream& os, const Matrix3D& mat) {
	for(int i=0; i<mat.rowSize; ++i)
		os << mat.getElement(i,0) <<" "<< mat.getElement(i,1) << " " <<
		      mat.getElement(i,2) <<" "<< mat.getElement(i,3) << std::endl;
	return os;
}

