#ifndef LOADEDDICESTRATEGY_H
#define LOADEDDICESTRATEGY_H
#include "dicestrategy.h"

class LoadedDiceStrategy: public DiceStrategy {
	public:
		int rollDice() override;
};

#endif