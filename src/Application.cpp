#include <Application.h>

#include <Utility.h>
#include <GUI/QSFMLCanvas.h>

#include <QApplication>
#include <QPushButton>
#include <QDockWidget>
#include <QString>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>

#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
//#include <dirent.h>
//#include <errno.h>

bool Application::instanceFlag = false;

Application* Application::single = NULL;

Application::Application(std::string assets)
   : dockUi(new Ui::PhysBDock), assets(assets), physB(), assetManager()
{
	//------------------ WINDOW SETUP ------------------------------------------------------
	QDockWidget *dockWidget = new QDockWidget;
	dockUi->setupUi(dockWidget);
	addDockWidget(Qt::BottomDockWidgetArea, dockWidget);

	// Set Initial State, then Connect signals and slots
	connect(dockUi->physBButton, SIGNAL(clicked()), this, SLOT(raytrace()));


	//---------------- SCENE DEFAULTS ----------------------------------------------------------------

	std::cout << "Beginning creation of defaults" << std::endl;

	// Create World Object
	// TODO LATER: this should go somewhere else, as it should always exist for any scene
	assetManager.add(Object(), "WORLD");
	//Object* worldObject = assetManager.get<Object>("WORLD");
	

	// Create default Environment
	assetManager.add(Environment(), "defaultEnvironment");
	//Environment* defaultEnv = assetManager.get<Environment>("defaultEnvironment");

	// Create a ForceEnvironment
	assetManager.add(ForceEnvironment(), "forceEnvironment");
	//ForceEnvironment* forceEnv01 = assetManager.get<ForceEnvironment>("forceEnvironment");

	// Create forces
	//assetManager.add(IndependentForce(Vector3D(0,-9.8,0)), "force01");
	IndependentForce* f1 = assetManager.get<IndependentForce>("force01");
	//assetManager.add(IndependentForce(Vector3D(-5,0,0)), "force02");
	IndependentForce* f2 = assetManager.get<IndependentForce>("force02");

	// Create Sphere
	//assetManager.add(Sphere(2), "sphere01");
	Sphere* sphere01 = assetManager.get<Sphere>("sphere01");

	// Create a RigidBody
	RigidBody rb = RigidBody(*worldObject,Vector3D(0,10,0),*sphere01,4,Vector3D(0,0,0),
	                  0.5f,0.8f, Vector3D(0,0,0));
	
	std::cout << rb.transform << std::endl;
	//assetManager.add( rb, "ball01");
	RigidBody* ball01 = assetManager.get<RigidBody>("ball01");

	std::cout << ball01->transform << std::endl;

	// Create QuadPlane
	//assetManager.add(QuadPlane(Vector3D(0,1,0), 20, 20), "qp01");
	QuadPlane* qp01 = assetManager.get<QuadPlane>("qp01");

	// Create a ColliderObject
	//assetManager.add( ColliderObject(*worldObject,Vector3D(0,-15,0),*qp01), "floor" );
	ColliderObject* floor = assetManager.get<ColliderObject>("floor");

	// Add sphere as renderable for ball
	ball01->setRenderable(sphere01);

	// Add quadplane as renderable for floor
	floor->setRenderable(qp01);

	// Add forces to ForceEnvironment
	forceEnv01->addForce(*f1, ForceEnvironment::ACCELERATION);
	forceEnv01->addForce(*f2, ForceEnvironment::FORCE);

	// Add ForceEnvironment to Environment
	defaultEnv->addForceEnvironment(*forceEnv01);

	// Add RigidBody and ColliderObject to Environment
	defaultEnv->addPhysical(*ball01);
	defaultEnv->addCollidable(*floor);

	// Link RigidBody to ForceEnvironment
	// TODO: use something besides index to link
	defaultEnv->linkForceEnv(0, 0);


	// Add Environment to Physics Engine
	physB.addEnvironment(*defaultEnv);

	/*
	// Create a ColliderObject
	ColliderObject* planeColl = new ColliderObject();
	ColliderObject& planeColl = defaultEnv.addNewColliderObject(Vector3D(0,-7,0));
	planeColl.addNewQuadPlaneCollider(Vector3D(0,1,0), 5, 5, Vector3D(0,0,0), "c01");
	*/

	std::cout << "All defaults successfully created" << std::endl;

	// ----------------------- Create a SFML view ------------------------------------------
	SFMLView = new QSFMLCanvas(this, QPoint(20, 20), QSize(360, 360), 60);
	SFMLView->addObject(ball01);
	SFMLView->addObject(floor);
	setCentralWidget(SFMLView);

	setWindowTitle("Physically Based");
	resize(900, 800);
}

void Application::create(std::string assets) {
   if(instanceFlag) return;   // if an instance already exists, do nothing
   else {                     // if instance doesn't exists, create it
      single = new Application(assets);
      instanceFlag = true;
   }
}

Application* Application::getInstance() {
    if(!instanceFlag) return NULL; // return NULL if no instance exists
    else return single;             // return existing instance
}

/*
int Application::getDir(std::string dir, std::vector<std::string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
       std::string filename = dirp->d_name;
       if(filename != "." && filename != "..")
        files.push_back(std::string(filename));
    }
    closedir(dp);
    return 0;
}
*/

// checks if a filename exists
bool Application::fexists(std::string filename) {
   std::ifstream ifile(filename.c_str());
   return ifile;
}

void Application::closeEvent(QCloseEvent *event) {
   physB.destroy();
}

void Application::raytrace() {
   physB.init();   // certain initializations that are necessary to do in the main thread
   physB.start();  // ray trace in a separate thread
}

void Application::customEvent(QEvent *event) {
   if (event->type() == PhysBEvent::traceStart) {
      //std::cout << "traceStart" << std::endl;
   }
   else if (event->type() == PhysBEvent::traceEnd) {
      //std::cout << "traceEnd" << std::endl;
      /*SFMLView->getImageCopy().saveToFile(assets+"\\renameMeNow.png");
      sceneManager->animAdvance();
      raytrace();// TODO: TEMPORARY!!!!!*/
   }
   else if (event->type() == PhysBEvent::tracePixelFilled) {
      QApplication::postEvent(SFMLView, new QEvent(QEvent::Paint));
      //std::cout << "tracePixelFilled" << std::endl;
   }

   else {
      QMainWindow::customEvent(event);
   }
}

