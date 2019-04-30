#include "glass.h"

Glass::Glass(int tileNumber, int tileValue)
	:Tile{tileNumber, "GLASS", tileValue}{};

void Glass::printSaveFormat(std::ostream &out){
	out << 2 << " " << this->getTileValue();
}
