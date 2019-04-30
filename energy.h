#ifndef ENERGY_H
#define ENERGY_H
#include "tile.h"

class Energy: public Tile {
	public:
		Energy(int tileNumber, int tileValue);
		void printSaveFormat(std::ostream &out) override;
};

#endif