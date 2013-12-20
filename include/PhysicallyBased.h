#ifndef PHYSICALLYBASED_H
#define PHYSICALLYBASED_H

#include <QThread>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include <PBTime.h>

class Environment;

/*
 * PHYSICALLYBASED
 *
 * This class is the main class for the physics engine.
 *
 */

// TODO LATER: Use something different than Qt's concurrency
class PhysicallyBased : public QThread {
	Q_OBJECT
public:
	typedef std::reference_wrapper<Environment> EnvironmentRef;
	
	PhysicallyBased();
	void destroy();
	void run();
	sf::Image* getImage() { return &image; }
	void init();
	void addEnvironment(Environment& e);

private slots:
	void simLoop();

private:
	sf::Image image; // TODO: get rid of this

	std::vector<EnvironmentRef> envs;
	size_t envSize;
	PBTime theTime;
};


#endif // PHYSICALLYBASED_H

