#include <Object.h>


Object::Object() : transform(0,0,0,*this,*this), renderable(NULL) {}

Object::Object(const Object& parent) : transform(0,0,0,parent, *this), renderable(NULL) {}

Object::Object(const Vector3D& pos, const Object& parent)
: transform(pos.elements[0],pos.elements[1],pos.elements[2],parent,*this), renderable(NULL)
{}


