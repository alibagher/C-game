#ifndef BOARDFACTORY_H
#define BOARDFACTORY_H
#include <iostream>
#include "board.h"

class BoardFactory {
	public:
		static Board *makeBoard(std::istream &in);
		static Board *makeRandomBoard(int seed);
};

#endif