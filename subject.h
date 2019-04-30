#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"

class Subject {
	std::vector<Observer*> observers;

	bool observerExists(Observer *o);
	
	public:
		Subject();
		void attach(Observer *o);
		virtual void notifyObservers() = 0;
		virtual ~Subject() = 0;

	protected:
		std::vector<Observer*> getObservers();
};

#endif