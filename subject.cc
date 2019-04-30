#include "subject.h"

Subject::Subject() {}
Subject::~Subject() {}

void Subject::attach(Observer *o){
	if (!observerExists(o)){
		observers.emplace_back(o);
	}
}

bool Subject::observerExists(Observer *o){
	for (auto it = observers.begin(); it != observers.end(); ++it){
		if (*it == o){
			return true;
		}
	}	

	return false;
}

std::vector<Observer*> Subject::getObservers(){
	return observers;
}