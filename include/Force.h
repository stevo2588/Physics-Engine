#ifndef FORCE_H
#define FORCE_H

#include <Utility.h>

#include <memory>
#include <functional>


// TODO: put this somewhere besides the global namespace
typedef std::unique_ptr<Force> ForcePtr;


class Force {
public:
	Vector3D get(const PBTime& theTime) const {
		return getForce(theTime) * flipped;
	}

	void flip() { flipped *= -1; }

	virtual ForcePtr clone() const=0;
protected:
	Force() : flipped(1) {}

	virtual Vector3D getForce(const PBTime& theTime) const=0;

	short flipped;
};


class IndependentForce : public Force {
public:
	IndependentForce(const Vector3D& f) : f(f) {
	}

	IndependentForce& operator+=(const IndependentForce& rhs) {
		this->f += rhs.f;
		return *this;
	}

	ForcePtr clone() const { return ForcePtr( new IndependentForce(*this) ); }

private:
	Vector3D getForce(const PBTime& theTime) const { return f; }

	Vector3D f;
};

inline IndependentForce operator+(IndependentForce lhs, const IndependentForce& rhs) {
	lhs += rhs;
	return lhs;
}


// DeferredForce
class DeferredForce : public Force {
public:
	DeferredForce( const std::function<Vector3D (const PBTime&)>& f )
	: force(f)
	{}

	ForcePtr clone() const { return ForcePtr( new DeferredForce(*this) ); }

protected:
	Vector3D getForce(const PBTime& theTime) const {
		return force(theTime); 
	}

	std::function<Vector3D (const PBTime&)> force;
};

/*
// Helper function for creating DeferredForce and returning a ForcePtr to it
template <typename... Args>
ForcePtr createDeferredForce( std::function<Vector3D (Args...)> f ) {
	return ForcePtr( new DeferredForce<Args...>(f) );
}
*/


/*
template <typename T>
class TimeDependentForce : public Force<T> {
public:
	TimeDependentForce(Vector3D (*updateFunc)(float)) : updateFunc(updateFunc) {
	}
	Vector3D get(float time, const T& o) const { return *updateFunc(time); }

private:
	Vector3D (*updateFunc)(float);
};

template <typename T>
class ObjectDependentForce : public Force<T> {
public:
	ObjectDependentForce(Vector3D (*updateFunc)(const T&)) {
	}
	Vector3D get(float time, const T& o) const { return *updateFunc(o); }

private:
	Vector3D (*updateFunc)(const T&);
};

template <typename T>
class TimeObjectDependentForce : public Force<T> {
public:
	TimeObjectDependentForce(Vector3D (*updateFunc)(float, const T&)) : updateFunc(updateFunc) {}
	Vector3D get(float time, const T& o) const { return *updateFunc(time,o); }

private:
	Vector3D (*updateFunc)(float,const T&);
};
*/


#endif // FORCE_H

