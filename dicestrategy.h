#ifndef DICESTRATEGY_H
#define DICESTRATEGY_H

class DiceStrategy {
	public:
		virtual int rollDice() = 0;
		virtual ~DiceStrategy();
};

#endif