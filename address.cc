#include <iomanip>
#include "address.h"
#include "player.h"
#include "tile.h"
#include "path.h"

Address::Address(int addressValue, int numDistributed)
	:addressValue{addressValue}, numDistributed{numDistributed}{}

void Address::doBuild(){
	this->getOwner()->addResidence(*this);
}

bool Address::improve(){
	if (this->numDistributed == 3){
		return false;
	}

	++this->numDistributed;
	return true;
}

int Address::getAddressValue(){
	return this->addressValue;
}

char Address::getTypeOfAddress() const {
	char c;

	switch (this->numDistributed){
		case 0: 
			c = 0;
			break;
		case 1: 
			c = 'B';
			break;
		case 2: 
			c = 'H';
			break;
		case 3: 
			c = 'T';
			break;
	}

	return c;	
}

int Address::getBuildingPoint(){
	return this->numDistributed;
}

void Address::notify(Address &whoNotified){
	this->setUnBuildable();
}

void Address::notify(Path &whoNotified){
	this->setPlayerCanBuild(whoNotified.getOwner());
}

void Address::notify(Tile &whoNotified){
	if (this->getOwner()){
		if (whoNotified.getTileName() == "BRICK"){
			this->getOwner()->setNumberOfBricks(
				getOwner()->getNumberOfBricks() + numDistributed);
			this->getOwner()->addDistributedResource("BRICK", numDistributed);

		} else if (whoNotified.getTileName() == "GLASS"){
			this->getOwner()->setNumberOfGlass(
				getOwner()->getNumberOfGlass() + numDistributed);
			this->getOwner()->addDistributedResource("GLASS", numDistributed);
		
		} else if (whoNotified.getTileName()== "HEAT"){
			this->getOwner()->setNumberOfHeat(
				getOwner()->getNumberOfHeat() + numDistributed);
			this->getOwner()->addDistributedResource("HEAT", numDistributed);
		
		} else if (whoNotified.getTileName() == "WIFI"){
			this->getOwner()->setNumberOfWifi(
				getOwner()->getNumberOfWifi() + numDistributed);
			this->getOwner()->addDistributedResource("WIFI", numDistributed);
		
		} else if (whoNotified.getTileName() == "ENERGY"){
			this->getOwner()->setNumberOfEnergy(
				getOwner()->getNumberOfEnergy() + numDistributed);
			this->getOwner()->addDistributedResource("ENERGY", numDistributed);
		}
	}
}

void Address::notifyObservers(){
	for (auto ob: this->getObservers()){
		ob->notify(*this);
	}
}

void Address::printSaveFormat(std::ostream &out){
	char c = getTypeOfAddress();
	out << this->addressValue << " " << c;
}

std::ostream &operator<<(std::ostream &out, Address &address){
	out << "|";

	char c = address.getTypeOfAddress();
	
	if (address.getOwner()){
		out << address.getOwner()->getName()[0] << c;
	} else {
		out << std::setw(2) << address.addressValue;
	}

	out << "|";
	return out;
}