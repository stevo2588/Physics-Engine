
#ifndef QSFMLCANVAS_HPP
#define QSFMLCANVAS_HPP

#include <SFML/OpenGL.hpp>
#include <GUI/renderWindowWrapper.h> 
#include <QWidget>
#include <QTimer>

class Object;

class QSFMLCanvas : public QWidget, public RWWrapper
{
   Q_OBJECT
public:
   ////////////////////////////////////////////////////////////
   /// \param Parent :    Parent of the widget
   /// \param Position :  Position of the widget
   /// \param Size :      Size of the widget
   ///////////////////////////////////////////////////////////
   QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime);
   virtual ~QSFMLCanvas();
   void addObject(const Object* o) { objects.push_back(o); }
   //void setVBOs(const std::vector<GLuint> *VBOIds);

protected:
   //void customEvent(QEvent *event);

private:
   void onInit(); // Notification that moment is good for doing initializations
   void resizeScene(GLsizei width, GLsizei height);

   void onUpdate(); // Notification that moment is good for doing its update and drawing stuff

   QPaintEngine* paintEngine() const; // Return the paint engine used by the widget to draw itself
   void showEvent(QShowEvent*); // Called when the widget is shown; we use it to initialize our SFML window
   void paintEvent(QPaintEvent*); // Called when the widget needs to be painted; we use it to display a new frame

   QTimer myTimer;       ///< Timer used to update the view
   bool   myInitialized; ///< Tell whether the SFML window has been initialized or not

   std::vector<const Object*> objects;
   //std::vector<GLuint> *VBOIds;
};


#endif // QSFMLCANVAS_HPP


