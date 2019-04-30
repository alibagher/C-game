#ifndef OBSERVER_H
#define OBSERVER_H

class Address;
class Path;
class Tile;

class Observer {
	public:
		virtual void notify(Address &whoNotified) = 0;
		virtual void notify(Path &whoNotified) = 0;
		virtual void notify(Tile &whoNotified);
		virtual ~Observer() = 0;
};

#endif
