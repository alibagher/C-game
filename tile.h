#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <string>
#include "subject.h"

class Tile: public Subject {
	int tileNumber;
	std::string tileName;
	int tileValue;
	bool geese;

	void notifyObservers() override;

	public:
		Tile(int tileNumber, std::string tileName, int tileValue);

		void giveResources();

		virtual void printSaveFormat(std::ostream &out) = 0;

		std::string getTileName();
		int getTileNumber();
		int getTileValue();
		bool hasGeese();

		void removeGeese();
		void setGeese();

		void setTileNumber(int tileNumber);
		void setTileValue(int tileValue);
};

#endif