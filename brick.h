#ifndef BRICK_H
#define BRICK_H
#include "tile.h"

class Brick: public Tile {
	public:
		Brick(int tileNumber, int tileValue);
		void printSaveFormat(std::ostream &out) override;
};

#endif