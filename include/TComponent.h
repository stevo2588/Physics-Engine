//-------------------------------------------------
//------------- TCOMPONENT_H --------------------------
//-------------------------------------------------
#ifndef TCOMPONENT_H
#define TCOMPONENT_H

#include <PBTransform.h>

// Class has a transform, but cannot exist within scene by itself. Must be a component of an
// object. This allows its transform to be traversed within the transform hierarchy.

class TComponent {
public:
	PBTransform transform;
};


#endif // TCOMPONENT_H



