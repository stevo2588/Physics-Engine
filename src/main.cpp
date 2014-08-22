//-------------------------------------------------
//------------- MAIN.CPP ---------------------
//------------- MAIN ENTRY POINT ------------------
//-------------------------------------------------

#include <iostream>
#include <vector>
#include <Application.h>
#include <QApplication>

int main(int argc, char* argv[])
{
   QApplication QApp(argc, argv);

   Application::create("D:/Development/MyProjects/Raytracer/RayTracer_CBProject/assets");
   Application *app = Application::getInstance();
   app->show();

   QApp.exec();

   return 0;
}

