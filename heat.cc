#include "heat.h"

Heat::Heat(int tileNumber, int tileValue)
	:Tile{tileNumber, "HEAT", tileValue}{};

void Heat::printSaveFormat(std::ostream &out){
	out << 3 << " " << this->getTileValue();
}