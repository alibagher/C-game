#include "park.h"

Park::Park(int tileNumber, int tileValue)
	:Tile{tileNumber, "PARK", -1}{};

void Park::printSaveFormat(std::ostream &out){
	out << 5 << " " << 7;
}