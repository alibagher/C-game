#ifndef HEAT_H
#define HEAT_H
#include "tile.h"

class Heat: public Tile {
	public:
		Heat(int tileNumber, int tileValue);
		void printSaveFormat(std::ostream &out) override;
};

#endif