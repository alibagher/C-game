#include "brick.h"

Brick::Brick(int tileNumber, int tileValue)
	:Tile{tileNumber, "BRICK", tileValue}{};

void Brick::printSaveFormat(std::ostream &out){
	out << 0 << " " << this->getTileValue();;
}