#ifndef WIFI_H
#define WIFI_H
#include "tile.h"

class Wifi: public Tile {
	public:
		Wifi(int tileNumber, int tileValue);
		void printSaveFormat(std::ostream &out) override;
};

#endif