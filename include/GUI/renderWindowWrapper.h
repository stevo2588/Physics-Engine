#ifndef RWWRAPPER_HPP
#define RWWRAPPER_HPP

#include <SFML/Graphics.hpp>

class RWWrapper : public sf::RenderWindow
{
public :
   void createRenderWindow(sf::WindowHandle wh) { create(wh); }
};


#endif // RWWRAPPER_HPP
