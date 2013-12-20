//-------------------------------------------------
//------------- UTILITY.H -----------------------
//-------------------------------------------------
#ifndef UTILITY_H
#define UTILITY_H

#include <sstream>

class Matrix3D;

//------------- Vector3D ----------------------------
class Vector3D {
private:
	const static size_t size = 3;

public:
	double elements[size];

	Vector3D();
	Vector3D(double x, double y, double z);

	double calcMagnitude() const;
	Vector3D normalize() const;
	Vector3D& operator=(const Vector3D &rhs);
	Vector3D& operator+=(const Vector3D &rhs);
	Vector3D& operator-=(const Vector3D &rhs);
	Vector3D operator-() const;
	friend Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
	friend Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
	double dotProduct(const Vector3D &v) const;
	Vector3D crossProduct(const Vector3D &v);

	// need the same with arguments switched?
	friend Vector3D operator*(const Vector3D &v1, const double s); 
	friend Vector3D operator/(const Vector3D &v1, const double s);
	friend Vector3D operator/(const Vector3D &v1, const float s);
	friend Vector3D operator*(const Matrix3D &s, const Vector3D &v);
	friend Vector3D m_mult_dirVec(const Matrix3D &s, const Vector3D &v);

	std::string toString() const {
	   std::ostringstream convert;
	   convert << "(" << elements[0] << "," << elements[1] << "," << elements[2] << ")";
	   return convert.str();
   }

	friend class PBTransform;
};

//------------- Vector2D ----------------------------
class Vector2D {
private:
	const static size_t size = 2;

public:
	double elements[size];

	Vector2D() {elements[0] = 0; elements[1] = 0;}
	Vector2D(double x, double y) {elements[0] = x; elements[1] = y;}

	std::string toString() const {
	   std::ostringstream convert;
	   convert << "(" << elements[0] << "," << elements[1] << ")";
	   return convert.str();
   }
};

//------------- Matrix3D ----------------------------
// A Specialized 4 x 4 matrix class for use with 3D transformations. The last row of the
// matrix is always [0 0 0 1]
class Matrix3D {
private:
	const static size_t rowSize = 4;
	const static size_t rowSizeMinus1 = 3;
	const static size_t columnSize = 4;

	double elements[rowSize][columnSize];

public:
	Matrix3D();
	Matrix3D(double elem[rowSize][columnSize]);
	Matrix3D(double x, double y, double z);
	void setIDMat();
	//template <size_t rows, size_t cols>
	void getElements(double (&e)[rowSize][columnSize]) const {
		for(int i=0; i<rowSize; i++) {
			for(int j=0; j<columnSize; j++) {
				e[i][j] = elements[i][j];
			}
		}
	}
	double getElem(int row, int column) const { return elements[row][column]; }

	// return true if matrix is invertible, stores inverse in invOut
	bool getInversion(Matrix3D &invOut) const;

	Matrix3D& operator=(const Matrix3D &rhs);
	friend Matrix3D operator*(const Matrix3D &s1, const Matrix3D &s2);

	std::string toString() const;

	friend class PBTransform;
	friend class Renderable;
};

//------------- HiDefColor ----------------------------
class HiDefColor {
public:
	float r,g,b;
public:
	HiDefColor() : r(0), g(0), b(0) {}
	HiDefColor(float r,float g,float b) : r(r),g(g),b(b) {}
	HiDefColor(const HiDefColor& clr) : r(clr.r), g(clr.g), b(clr.b) {}
	HiDefColor& operator=(const HiDefColor &rhs);
	HiDefColor& operator+=(const HiDefColor &rhs);
	friend HiDefColor operator+(const HiDefColor &c1, const HiDefColor &c2);
	friend HiDefColor operator-(const HiDefColor &c1, const HiDefColor &c2);
	friend HiDefColor operator*(const HiDefColor &lhs, double rhs);
};

//-------------------------- MISC ------------------------------------------
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v );

#endif // UTILITY_H
