#ifndef RENDERABLE_H
#define RENDERABLE_H


class Renderable {
public:
	Renderable() {}

	virtual void openGLDraw() const=0;

protected:
	
};


#endif // RENDERABLE_H
