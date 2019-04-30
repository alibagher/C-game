#ifndef GLASS_H
#define GLASS_H
#include "tile.h"

class Glass: public Tile {
	public:
		Glass(int tileNumber, int tileValue);
		void printSaveFormat(std::ostream &out) override;
};

#endif