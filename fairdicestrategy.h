#ifndef FAIRDICESTRATEGY_H
#define FAIRDICESTRATEGY_H
#include "dicestrategy.h"

class FairDiceStrategy: public DiceStrategy {
	public:
		int rollDice() override;
};

#endif