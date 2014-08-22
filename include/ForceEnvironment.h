#ifndef FORCEENVIRONMENT_H
#define FORCEENVIRONMENT_H

#include <functional>
#include <vector>
#include <Force.h>

class ForceEnvironment {
public:
	typedef std::reference_wrapper<const Force> ForceRef;

	ForceEnvironment() {}

	enum forceType { FORCE, ACCELERATION };

	void addForce(const Force& f, forceType t) {
		if(t == FORCE) forces.push_back( ForceRef(f) );
		else if(t == ACCELERATION) accels.push_back( ForceRef(f) );
	}

	friend class Environment;

private:
	std::vector<ForceRef> forces;
	std::vector<ForceRef> accels;
};

#endif // FORCEENVIRONMENT_H

