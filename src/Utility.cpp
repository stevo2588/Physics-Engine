//-------------------------------------------------
//------------- UTILITY.CPP -----------------------
//-------------------------------------------------
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <Utility.h>

//------------- Vector3D ----------------------------
Vector3D::Vector3D() {
	elements[0] = 0;
	elements[1] = 0;
	elements[2] = 0;
}

Vector3D::Vector3D(double x, double y, double z) {
	elements[0] = x;
	elements[1] = y;
	elements[2] = z;
}

double Vector3D::calcMagnitude() const {
   return sqrt(elements[0]*elements[0]+elements[1]*elements[1]+elements[2]*elements[2]);
}

Vector3D Vector3D::normalize() const {
   double mag = calcMagnitude();
   return Vector3D(elements[0]/mag,elements[1]/mag,elements[2]/mag);
}

double Vector3D::dotProduct(const Vector3D &v) const {
	double prod = this->elements[0]*v.elements[0] + this->elements[1]*v.elements[1] + this->elements[2]*v.elements[2];
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

double operator*(const Vector3D &v1, const Vector3D &v2) {
	return v1.elements[0]*v2.elements[0] +
	       v1.elements[1]*v2.elements[1] +
	       v1.elements[2]*v2.elements[2];
}

Vector3D operator*(const Vector3D &v1, const double s) {
   return Vector3D(v1.elements[0]*s,v1.elements[1]*s,v1.elements[2]*s);
}

Vector3D operator/(const Vector3D &v1, const double s) {
   try {
      return Vector3D(v1.elements[0]/s,v1.elements[1]/s,v1.elements[2]/s);
   }
   catch(const std::logic_error &) {
      std::cout << "Division by 0" << std::endl;
   }

   return Vector3D(0, 0, 0);
}

Vector3D operator/(const Vector3D &v1, const float s) {
   try {
      return Vector3D(v1.elements[0]/s,v1.elements[1]/s,v1.elements[2]/s);
   }
   catch(const std::logic_error &) {
      std::cout << "Division by 0" << std::endl;
   }

   return Vector3D(0, 0, 0);
}

Vector3D operator*(const Matrix3D &s, const Vector3D &v) { // technically post-multiplication
	Vector3D prod(0,0,0);

	prod.elements[0] = s.elements[0][0]*v.elements[0] + s.elements[0][1]*v.elements[1] +
	                   s.elements[0][2]*v.elements[2] + s.elements[0][3];
	prod.elements[1] = s.elements[1][0]*v.elements[0] + s.elements[1][1]*v.elements[1] +
	                   s.elements[1][2]*v.elements[2] + s.elements[1][3];
	prod.elements[2] = s.elements[2][0]*v.elements[0] + s.elements[2][1]*v.elements[1] +
	                   s.elements[2][2]*v.elements[2] + s.elements[2][3];

	return prod;
}

// no translation, for use with direction vectors
Vector3D m_mult_dirVec(const Matrix3D &s, const Vector3D &v) {
	Vector3D prod(0,0,0);

	prod.elements[0] = s.elements[0][0]*v.elements[0] + s.elements[0][1]*v.elements[1] +
	                   s.elements[0][2]*v.elements[2];
	prod.elements[1] = s.elements[1][0]*v.elements[0] + s.elements[1][1]*v.elements[1] +
	                   s.elements[1][2]*v.elements[2];
	prod.elements[2] = s.elements[2][0]*v.elements[0] + s.elements[2][1]*v.elements[1] +
	                   s.elements[2][2]*v.elements[2];

	return prod;
}

//------------- Matrix3D ----------------------------------------------------------
// A Specialized 4 x 4 matrix class for use with 3D transformations.
Matrix3D::Matrix3D() {
	setIDMat();
}

Matrix3D::Matrix3D(double elem[rowSize][columnSize]) {
	for(int i=0; i<rowSizeMinus1; ++i)
		for(int j=0; j<columnSize; ++j)
			elements[i][j] = elem[i][j];
}

Matrix3D::Matrix3D(double x, double y, double z) {
	elements[0][0] = 1; elements[0][1] = 0; elements[0][2] = 0; elements[0][3] = x;
	elements[1][0] = 0; elements[1][1] = 1; elements[1][2] = 0; elements[1][3] = y;
	elements[2][0] = 0; elements[2][1] = 0; elements[2][2] = 1; elements[2][3] = z;
}

void Matrix3D::setIDMat() {
	elements[0][0] = 1; elements[0][1] = 0; elements[0][2] = 0; elements[0][3] = 0;
	elements[1][0] = 0; elements[1][1] = 1; elements[1][2] = 0; elements[1][3] = 0;
	elements[2][0] = 0; elements[2][1] = 0; elements[2][2] = 1; elements[2][3] = 0;
}

bool Matrix3D::getInversion(Matrix3D &invOut) const {
	Matrix3D inv;
	double det;

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

Matrix3D& Matrix3D::operator=(const Matrix3D &rhs) {
	if(this != &rhs) {
		// Deallocate, allocate new space, copy values
		for(int i=0; i<rowSizeMinus1; ++i)
			for(int j=0; j<columnSize; ++j)
				elements[i][j] = rhs.getElem(i,j);
	}
	return *this;
}

// Specialized for 3D Transformations (acts as if all matrices have a 4th row with [0 0 0 1])
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

std::string Matrix3D::toString() const {
	std::ostringstream convert;
	for(int i=0; i<rowSize; ++i)
		convert << elements[i][0] << elements[i][1] << elements[i][2] << elements[i][3]
		<< std::endl;
	return convert.str();
}


//------------- HiDefColor ----------------------------
HiDefColor& HiDefColor::operator=(const HiDefColor &rhs) {
	if(this != &rhs) {
		// Deallocate, allocate new space, copy values
		this->r = rhs.r;
		this->g = rhs.g;
		this->b = rhs.b;
	}
	return *this;
}

HiDefColor operator+(const HiDefColor &c1, const HiDefColor &c2) {
   return HiDefColor(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);
}

HiDefColor& HiDefColor::operator+=(const HiDefColor &rhs) {
   if(this != &rhs) {
		/*this->r = rhs.r + this->r;
		this->g = rhs.g + this->g;
		this->b = rhs.b + this->b;*/
		*this = rhs + *this;
	}
	return *this;
}

HiDefColor operator*(const HiDefColor &lhs, double rhs) {
   return HiDefColor(lhs.r*rhs, lhs.g*rhs, lhs.b*rhs);
}

//-------------------------- MISC ------------------------------------------
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}
}
