#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "address.h"
#include "path.h"
#include "dicestrategy.h"

class BluePlayer;
class RedPlayer;
class OrangePlayer;
class YellowPlayer;

class Board;

class Player {
	std::string name;

	int numberOfBricks;
	int numberOfEnergy;
	int numberOfHeat;
	int numberOfGlass;
	int numberOfWifi;

	std::vector<Address*> addresses;
	std::vector<Path*> paths;
	DiceStrategy *dice;

	std::map<std::string, int> distributedResources;

	public:
		Player(std::string name);

		bool improve(Board &board, int addressNum);
		void addResidence(Address &address);
		void addRoad(Path &path);
		
		std::map<std::string, int> getDistributedResources();
		void addDistributedResource(std::string resource, int numDistributed);
		void clearDistributedResources();
		
		int rollDice();
		void loseResources();
		std::string steal(Player *stealer);

		void printResidences(std::ostream &out) const;
		void printStatus(std::ostream &out) const;
		void printSaveFormat(std::ostream &out) const;

		std::string getName();
		int getNumberOfBricks();
		int getNumberOfEnergy();
		int getNumberOfHeat();
		int getNumberOfGlass();
		int getNumberOfWifi();
		int getTotalResources();
		int getPoints();
		Address *getAddress(int addressValue);

		void setNumberOfBricks(int numberOfBricks);
		void setNumberOfEnergy(int numberOfEnergy);
		void setNumberOfHeat(int numberOfHeat);
		void setNumberOfGlass(int numberOfGlass);
		void setNumberOfWifi(int numberOfWifi);
		void setLoadedDice();
		void setFairDice();

		void clear();

		virtual ~Player() = 0;
};

#endif
