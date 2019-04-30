#include "wifi.h"

Wifi::Wifi(int tileNumber, int tileValue)
	:Tile{tileNumber, "WIFI", tileValue}{};

void Wifi::printSaveFormat(std::ostream &out){
	out << 4 << " " << this->getTileValue();
}