#ifndef PARK_H
#define PARK_H
#include "tile.h"

class Park: public Tile {
	public:
		Park(int tileNumber, int tileValue = -1);
		void printSaveFormat(std::ostream &out) override;
};

#endif