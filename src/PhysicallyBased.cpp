#include <cmath>
#include <ctime>
#include <QApplication>
#include <QMessageBox>
#include <Application.h>
#include <PhysicallyBased.h>
#include <GUI/QSFMLCanvas.h>
#include <Utility.h>
#include <Events.h>
#include <Environment.h>

PhysicallyBased::PhysicallyBased() : envSize(0) {
	moveToThread(this);
	
	/*
	//Initialise VBO - do only once, at start of program
	GLuint triangleVboId; //Create a variable to hold the VBO identifier
	VBOIds.push_back(triangleVboId);
	float data[] = {1.0, 0.0, 1.0, 0.0, 0.0, -1.0, -1.0, 0.0, 1.0}; //Vertices of a triangle (counter-clockwise winding)
	glGenBuffers(1, &triangleVboId); //Create a new VBO and use the variable id to store the VBO id
	glBindBuffer(GL_ARRAY_BUFFER, triangleVboId); //Make the new VBO active
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW); //Upload vertex data to the video device
	*/
}

void PhysicallyBased::destroy() {
	//rp->deleteScene();
}

// add a new Environment
void PhysicallyBased::addEnvironment(Environment& e) {
	envs.push_back( EnvironmentRef(e) );
	envSize++;
}

void PhysicallyBased::init() {
	image = sf::Image();
	//image.create(rp->pixelWidth,rp->pixelHeight);
}

void PhysicallyBased::run() {
	srand( time(NULL) );
	
	QTimer* timer = new QTimer(this);
	float timestepMS = theTime.timestep * 1000;
	timer->setInterval(timestepMS);
	timer->connect(timer, SIGNAL(timeout()), this, SLOT(simLoop()));
	timer->start();
	
	exec(); // start event loop
	
	//Application* mainApp = Application::getInstance();
	//QApplication::postEvent(mainApp, new QEvent(PhysBEvent::traceStart));
	//QApplication::postEvent(mainApp->SFMLView, new QEvent(PhysBEvent::tracePixelFilled));
	//QApplication::postEvent(eventManager, new QEvent(PhysBEvent::tracePixelFilled));
	//QApplication::postEvent(mainApp, new QEvent(PhysBEvent::traceEnd));
}

void PhysicallyBased::simLoop() {

	// for each environment
	for( auto &i: envs ) {
		i.get().update(theTime);
	}

	// update elapsed time
	theTime.elapsedTime += theTime.timestep;
}


