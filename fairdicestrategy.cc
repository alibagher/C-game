#include <iostream>
#include <cstdlib>
#include <ctime>
#include "fairdicestrategy.h"

int FairDiceStrategy::rollDice(){
	srand(time(0));
	int roll = 0;
	roll += (rand() % 6) + 1;
	roll += (rand() % 6) + 1;

	#ifdef DEBUG
	std::cout << "Fair Dice Rolled: " << roll << std::endl;
	#endif

	return roll;
}