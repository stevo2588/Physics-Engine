//-------------------------------------------------
//------------- UTILITY.H -----------------------
//-------------------------------------------------
#ifndef UTILITY_H
#define UTILITY_H

class Matrix3D;

#include <cstddef>
#include <array>
#include <ostream>

//------------- Vector3D ----------------------------
class Vector3D {
private:
	const static size_t size = 3;

public:
	float elements[size];

	Vector3D();
	Vector3D(float x, float y, float z);

	float calcMagnitude() const;
	Vector3D normalize() const;
	Vector3D& operator=(const Vector3D &rhs);
	Vector3D& operator+=(const Vector3D &rhs);
	Vector3D& operator-=(const Vector3D &rhs);
	Vector3D operator-() const;
	friend Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
	friend Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
	float dotProduct(const Vector3D &v) const;
	Vector3D crossProduct(const Vector3D &v);

	// need the same with arguments switched?
	friend Vector3D operator*(const Vector3D &v1, const float s); 
	friend Vector3D operator/(const Vector3D &v1, const float s);
	friend Vector3D operator*(const Matrix3D &s, const Vector3D &v);
	friend Vector3D m_mult_dirVec(const Matrix3D &s, const Vector3D &v);

	friend std::ostream& operator<< (std::ostream &os, const Vector3D& vec);
	friend class PBTransform;
};

//------------- Vector2D ----------------------------
class Vector2D {
private:
	const static size_t size = 2;

public:
	float elements[size];

	Vector2D() {elements[0] = 0; elements[1] = 0;}
	Vector2D(float x, float y) {elements[0] = x; elements[1] = y;}

	friend std::ostream& operator<< (std::ostream &os, const Vector2D& vec);
};

//------------- Matrix3D ----------------------------
// A Specialized 4 x 4 matrix class for use with 3D transformations. The last row of the
// matrix is always [0 0 0 1]
class Matrix3D {
private:
	const static unsigned short rowSize = 4;
	const static unsigned short rowSizeMinus1 = 3;
	const static unsigned short columnSize = 4;
	const static unsigned short arraySize = rowSize * columnSize;

	//float elements[rowSize][columnSize];
	std::array<float, arraySize> elements;

	unsigned short getIndex(unsigned short row, unsigned short column) const {
		return row*rowSize + column;
	}

	float& getElementRef(int row, int column) {
		return elements[getIndex(row,column)];
	}

public:
	Matrix3D();
	Matrix3D(nullptr_t n);
	//Matrix3D(float elem[rowSize][columnSize]);
	Matrix3D(float x, float y, float z);
	void setIDMat();
	//template <size_t rows, size_t cols>
	/*void getElements(float (&e)[rowSize][columnSize]) const {
		for(int i=0; i<rowSize; i++) {
			for(int j=0; j<columnSize; j++) {
				e[i][j] = elements[i][j];
			}
		}
	}*/

	const float* getElements() const { return elements.data(); }
	
	//float getElem(int row, int column) const { return elements[row][column]; }
	float getElement(int row, int column) const { return elements[getIndex(row,column)]; }

	// return true if matrix is invertible, stores inverse in invOut
	bool getInversion(Matrix3D &invOut) const;

	Matrix3D& operator=(const Matrix3D &rhs);
	friend Matrix3D operator*(const Matrix3D &s1, const Matrix3D &s2);
	friend Vector3D operator*(const Matrix3D &s, const Vector3D &v);

	friend std::ostream& operator<<(std::ostream& os, const Matrix3D& mat);
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
