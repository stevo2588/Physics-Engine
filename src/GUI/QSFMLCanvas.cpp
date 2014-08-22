
#include <GL/glew.h>
//#include <SFML/OpenGL.hpp>
#include <GUI/QSFMLCanvas.h>
#include <GUI/renderWindowWrapper.h>
#include <QApplication>
#include <PhysicallyBased.h>
#include <Object.h>
#include <Events.h>
#include <Utility.h>

#include <iostream> // remove me
#include <cmath>

// Platform-specific headers
#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

QSFMLCanvas::QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size,
                         unsigned int FrameTime) : QWidget(Parent), myInitialized (false)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    move(Position);
    resize(Size);

    // Setup the timer (only necessary if you want the widget to automatically and continuously repaint itself)
    myTimer.setInterval(FrameTime);
}

QSFMLCanvas::~QSFMLCanvas() {}

void QSFMLCanvas::onInit() {
	/* Enable a single OpenGL light. */
	//GLfloat light_diffuse[] = {0.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glShadeModel(GL_SMOOTH);                    // Enables Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);       // Black Background
	glClearDepth(1.0f);                         // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                    // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                     // The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);     // Really Nice Perspective Calculations
	
	sf::Vector2u size = getSize();
	resizeScene((GLsizei)size.x, (GLsizei)size.y);
}

void QSFMLCanvas::resizeScene(GLsizei width, GLsizei height) {
	if (height==0) height=1;   // prevent division by zero by

	glViewport(0, 0, width, height); // adjust the viewport when the window is resized
	
	glMatrixMode(GL_PROJECTION);           // Select The Projection Matrix
	glLoadIdentity();                      // Reset The Projection Matrix
 
	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	// The following code is a fancy bit of math that is eqivilant to calling:
	// gluPerspective( fieldOfView/2.0f, width/height , 0.1f, 255.0f )
	// We do it this way simply to avoid requiring glu.h
	GLfloat zNear = 0.1f;
	GLfloat zFar = 100.0f;
	GLfloat aspect = float(width)/float(height);
	GLfloat fH = tan( float(90.0f / 360.0f * 3.14159f) ) * zNear;
	GLfloat fW = fH * aspect;
	glFrustum( -fW, fW, -fH, fH, zNear, zFar );
 
	glMatrixMode(GL_MODELVIEW);                 // Select The Modelview Matrix
	glLoadIdentity();                           // Reset The Modelview Matrix
}

void QSFMLCanvas::onUpdate() {
	
	setVerticalSyncEnabled(true);

	// handle events
	sf::Event event;
	while (pollEvent(event)) {
		if (event.type == sf::Event::Resized) {
			resizeScene((GLsizei)event.size.width, (GLsizei)event.size.height);
		}
	}

	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glCullFace(GL_FRONT);
	//glEnable(GL_CULL_FACE);
	

	glLoadIdentity();//load identity matrix
	
	// Inverse camera position
	glTranslatef(0,0,-20);
	//glRotatef(45.0f,0,1,0);
	glPushMatrix();

	// for each object, call its draw function
	int objSize = objects.size();
	for(int i=0; i<objSize; i++) {
		glPushMatrix();
		//std::cout << objects[i]->transform << std::endl;
		glMultTransposeMatrixf(objects[i]->transform.getTransform().getElements());

		objects[i]->getRenderable()->openGLDraw();
		glPopMatrix();
	}

	glPopMatrix();
    

/*
	//Draw Triangle from VBO - do each time window, view point or data changes
	//Establish its 3 coordinates per vertex with zero stride in this array; necessary here
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVboId); //Make the new VBO active. Repeat here incase changed since initialisation
	glEnableClientState(GL_VERTEX_ARRAY); //Establish array contains vertices (not normals, colours, texture coords etc)
	glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float) / 3); //Actually draw the triangle, giving the number of vertices provided

	//Force display to be drawn now
	//glFlush();
*/

	// end the current frame (internally swaps the front and back buffers)
	display();
}

QPaintEngine* QSFMLCanvas::paintEngine() const {
    return 0;
}

void QSFMLCanvas::showEvent(QShowEvent*) {
    if (!myInitialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // Create the SFML window with the widget handle
        createRenderWindow(winId()); // creates sfml window from the existing Qt window

        onInit(); // initialize

		glewInit(); // initialize GLEW

        // Setup the timer to trigger a refresh at specified framerate (only necessary if you want the widget to automatically and continuously repaint itself)
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();

        myInitialized = true;
    }
}

void QSFMLCanvas::paintEvent(QPaintEvent*) {
    onUpdate(); // update
    display(); // Display on screen
}
