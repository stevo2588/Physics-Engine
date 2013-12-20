// Stephen Aldriedge

#ifndef APPLICATION_H
#define APPLICATION_H

#include <AssetManager.h>
#include <PhysicallyBased.h>
#include <ui_PhysicallyBased.h>
#include <ColliderObject.h>
#include <Environment.h>
#include <Events.h>
#include <Force.h>
#include <ForceEnvironment.h>
#include <Object.h>
#include <QuadPlane.h>
#include <RigidBody.h>
#include <Sphere.h>


#include <QMainWindow>
#include <QtGui>

#include <fstream>
#include <iostream>
#include <sstream>


class QSFMLCanvas;

//----------------------- APPLICATION ----------------------------------------

class Application : public QMainWindow {

	Q_OBJECT
private:
	Application(std::string assets);	// private constructor

public:
	static void create(std::string assets);
	static Application* getInstance(); // get a pointer to the instance
	~Application() { instanceFlag = false; }

	friend class PhysicallyBased;

protected:
	void closeEvent(QCloseEvent *event);
	void customEvent(QEvent *event);

private:
	static bool instanceFlag;	 // tells us if an instance exists
	static Application *single;  // pointer to the application instance

	Ui::PhysBDock* dockUi;

	const std::string assets;

	PhysicallyBased physB;

	// AssetManager for managing all assets used. Make sure to not use abstract classes!
	AssetManager<Environment, ForceEnvironment, IndependentForce, Object, ColliderObject,
	             RigidBody, QuadPlane, Sphere> assetManager;

	QSFMLCanvas* SFMLView;
	std::string saveFileName;

	int getDir(std::string dir, std::vector<std::string> &files);
	bool fexists(std::string filename);
	void resizeMe(int width, int height);
	void display(int width, int height);

private slots:
	void raytrace();

};

#endif // APPLICATION_H

