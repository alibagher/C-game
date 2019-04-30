#include <iostream>
#include <sstream>
#include "loadeddicestrategy.h"

int LoadedDiceStrategy::rollDice(){
	int roll = 0;

	std::string input;
	std::cout << "Input a roll between 2 and 12:" << std::endl;

	while (std::cout << "> " && std::cin >> input){
		std::istringstream iss {input};

		if (!(iss >> roll) || roll < 2 || roll > 12){
			std::cout << "Invalid roll." << std::endl;
			std::cout << "Input a roll between 2 and 12:" << std::endl;
		} else {
			break;
		}
	}

	return roll;
}