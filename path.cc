#include <iomanip>
#include "address.h"
#include "path.h"
#include "player.h"

Path::Path(int pathValue): pathValue{pathValue}{};

int Path::getPathValue(){
	return this->pathValue;
}

void Path::doBuild(){
	this->getOwner()->addRoad(*this);
}

void Path::notify(Address &whoNotified){
	this->setPlayerCanBuild(whoNotified.getOwner());
}

void Path::notify(Path &whoNotified){
	this->setPlayerCanBuild(whoNotified.getOwner());
}

void Path::notifyObservers(){
	for (auto ob : this->getObservers()){
		ob->notify(*this);
	}
}

void Path::printSaveFormat(std::ostream &out){
	out << this->pathValue;
}

std::ostream &operator<<(std::ostream &out, Path &path){
	if (path.getOwner()){
		out << path.getOwner()->getName()[0] << "R";
	} else {
		out << std::setw(2) << path.pathValue;
	}

	return out;
}