#ifndef ADDRESS_H
#define ADDRESS_H
#include <iostream>
#include "constructable.h"

class Path;
class Tile;

class Address: public Constructable {
	int addressValue;
	int numDistributed;

	public:
		Address(int addressValue, int numDistributed = 0);

		void doBuild() override;
		bool improve();

		char getTypeOfAddress() const;
		int getAddressValue();
		int getBuildingPoint();

		void notify(Address &whoNotified) override;
		void notify(Path &whoNotified) override;
		void notify(Tile &whoNotified) override;
		void notifyObservers() override;

		void printSaveFormat(std::ostream &out) override;
	
	
	friend std::ostream &operator<<(std::ostream &out, Address &address);
};

#endif
