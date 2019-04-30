#include "energy.h"

Energy::Energy(int tileNumber, int tileValue)
	:Tile{tileNumber, "ENERGY", tileValue}{};

void Energy::printSaveFormat(std::ostream &out){
	out << 1 << " " << this->getTileValue();
}