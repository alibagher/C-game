#include "player.h"
#include "loadeddicestrategy.h"
#include "fairdicestrategy.h"

Player::Player(std::string name): name{name}, numberOfBricks{0}, 
numberOfEnergy{0}, numberOfHeat{0}, numberOfGlass{0}, numberOfWifi{0},
dice{new LoadedDiceStrategy()}{}

Player::~Player(){
	delete dice;
}

void Player::clearDistributedResources(){
	this->distributedResources.clear();
}

std::map<std::string, int> Player::getDistributedResources(){
	return this->distributedResources;
}

void Player::addDistributedResource(std::string resource, int numDistributed){
	this->distributedResources[resource] += numDistributed;
}

int Player::rollDice(){
	return this->dice->rollDice();
}

bool Player::improve(Board &board, int addressNum){
	for (auto it: this->addresses){
		if ((*it).getAddressValue() == addressNum){
			return (*it).improve();
		}
	}
	
	return false;
}

void Player::loseResources(){
	int totalResources = getTotalResources();

	if (totalResources >= 10){
		std::vector<int> resource{numberOfBricks, numberOfEnergy, 
			numberOfHeat, numberOfGlass, numberOfWifi};

		int numLost = totalResources / 2;

		std::cout << "Builder " << name <<  " loses " << numLost;
		std::cout << " resources to the geese. They lose:" << std::endl;

		srand(time(0));
		int i = 0;

		while (i != numLost){
			int index = rand() % 5;

			if (index == 0 && resource[0] > 0){
				--resource[0];
				++i;
			} else if (index == 1 && resource[1] > 0){
				--resource[1];
				++i;
			} else if (index == 2 && resource[2] > 0){
				--resource[2];
				++i;
			} else if (index == 3 && resource[3] > 0){
				--resource[3];
				++i;
			} else if (index == 4 && resource[4] > 0){
				--resource[4];
				++i;
			}
		}

		if ((numberOfBricks - resource[0]) != 0){
			std::cout << numberOfBricks - resource[0] << " BRICK";
			std::cout << std::endl;
		}

		if ((numberOfEnergy - resource[1]) != 0){
			std::cout << numberOfEnergy - resource[1] << " ENERGY";
			std::cout << std::endl;
		}

		if ((numberOfHeat - resource[2]) != 0){
			std::cout << numberOfHeat - resource[2] << " HEAT";
			std::cout << std::endl;
		}

		if ((numberOfGlass - resource[3]) != 0){
			std::cout << numberOfGlass - resource[3] << " GLASS";
			std::cout << std::endl;
		}

		if ((numberOfWifi - resource[4]) != 0){
			std::cout << numberOfWifi - resource[4] << " WIFI";
			std::cout << std::endl;
		}

		this->numberOfBricks = resource[0];
		this->numberOfEnergy = resource[1];
		this->numberOfHeat = resource[2];
		this->numberOfGlass = resource[3];
		this->numberOfWifi = resource[4]; 
	}
}

std::string Player::steal(Player *stealer){
	int total = getTotalResources();
	std::string out = "";

	while (true){
		if (getTotalResources() == 0){
			break;
		}

		int brickProb = numberOfBricks/total*100;
		int energyProb = numberOfEnergy/total*100;
		int heatProb = numberOfHeat/total*100;
		int wifiProb = numberOfWifi/total*100;
		int glassProb = numberOfGlass/total*100;

		int brickRandProb = rand() % 100;
		int energyRandProb = rand() % 100;
		int heatRandProb = rand() % 100;
		int wifiRandProb = rand() % 100;
		int glassRandProb = rand() % 100;

		brickProb *= brickRandProb;
		energyProb *= energyRandProb;
		heatProb *= heatRandProb;
		wifiProb *= wifiRandProb;
		glassProb *= glassRandProb;

		if (brickProb >= energyProb && brickProb >= heatProb && brickProb >= wifiProb && brickProb >= glassProb){
	    	if (!(this->numberOfBricks <= 0)){
	    		out = "brick";
	    		this->numberOfBricks -= 1;
	    		stealer->setNumberOfBricks(getNumberOfBricks() + 1);
	    		break;
	    	}
		} else if (energyProb >= wifiProb && energyProb >= brickProb && energyProb >= glassProb && energyProb >= heatProb){
			if (!(this->numberOfEnergy <= 0)){
	   			out = "energy";
	   			this->numberOfEnergy -= 1;
	    		stealer->setNumberOfEnergy(getNumberOfEnergy() + 1);
	    		break;
	    	}
		} else if (heatProb >= wifiProb && heatProb >= brickProb && heatProb >= glassProb && heatProb >= energyProb){
	    	if (!(this->numberOfHeat <= 0)){
	    		out = "heat";
	    		this->numberOfHeat -= 1;
	    		stealer->setNumberOfHeat(getNumberOfHeat() + 1);
	    		break;
	    	}
		} else if (wifiProb >= energyProb && wifiProb >= brickProb && wifiProb >= glassProb && wifiProb >= heatProb){
		    if (!(numberOfWifi <= 0)){
		    	out = "wifi";
		    	this->numberOfWifi -= 1;
	    		stealer->setNumberOfWifi(getNumberOfWifi() + 1);
	    		break;
	    	}
		} else if (glassProb >= energyProb && glassProb >= brickProb && glassProb >= heatProb && glassProb >= wifiProb) {
	    	if (!(numberOfGlass <= 0)){
	   		 	out = "glass";
	   	 		this->numberOfGlass -= 1;
	    		stealer->setNumberOfGlass(getNumberOfGlass() + 1);
	    		break;
	    	}
	    }
	}

	return out;
}

void Player::printResidences(std::ostream &out) const {
	out << this->name << " has built:" << std::endl;

	for (auto it: this->addresses){
		out << (*it).getAddressValue() << " " << (*it).getTypeOfAddress();
		out << std::endl;
	}
}

void Player::printStatus(std::ostream &out) const {
	int buildingPoints = 0;

	for (auto it: this->addresses){
		buildingPoints += (*it).getBuildingPoint();
	}

	out << this->name << " has " << buildingPoints << " building points, ";
	out << this->numberOfBricks << " brick, " << this->numberOfEnergy;
	out << " energy, " << this->numberOfGlass << " glass, ";
	out << this->numberOfHeat << " heat, and " << this->numberOfWifi;
	out << " WiFi.";
}

void Player::printSaveFormat(std::ostream &out) const {
	out << this->numberOfBricks << " " << this->numberOfEnergy << " "
	    << this->numberOfGlass << " " << this->numberOfHeat << " "
	    << this->numberOfWifi << " ";

	out << "r ";

	for (auto it: this->paths){
		(*it).printSaveFormat(out);
		out << " ";
	}

	out << "h ";

	for (auto it: this->addresses){
		(*it).printSaveFormat(out);
		out << " ";
	}
}

std::string Player::getName(){
	return this->name;
}

int Player::getNumberOfBricks(){
	return this->numberOfBricks;
}

int Player::getNumberOfEnergy(){
	return this->numberOfEnergy;
}

int Player::getNumberOfHeat(){
	return this->numberOfHeat;
}

int Player::getNumberOfGlass(){
	return this->numberOfGlass;
}

int Player::getNumberOfWifi(){
	return this->numberOfWifi;
}

int Player::getTotalResources(){
	return this->numberOfBricks + this->numberOfEnergy + 
		   this->numberOfHeat + this->numberOfGlass + this->numberOfWifi;
}

int Player::getPoints(){
	int points = 0;
	for (auto it: this->addresses){
		points += (*it).getBuildingPoint();
	}

	return points; 
}

Address *Player::getAddress(int addressValue){
	for (auto it: this->addresses){
		if ((*it).getAddressValue() == addressValue){
			return it;
		}
	}

	return nullptr;
}

void Player::addResidence(Address &address){
	this->addresses.emplace_back(&address);
}

void Player::addRoad(Path &path){
	this->paths.emplace_back(&path);
}

void Player::setNumberOfBricks(int numberOfBricks){
	this->numberOfBricks = numberOfBricks;
}

void Player::setNumberOfEnergy(int numberOfEnergy){
	this->numberOfEnergy = numberOfEnergy;
}

void Player::setNumberOfHeat(int numberOfHeat){
	this->numberOfHeat = numberOfHeat;
}

void Player::setNumberOfGlass(int numberOfGlass){
	this->numberOfGlass = numberOfGlass;
}

void Player::setNumberOfWifi(int numberOfWifi){
	this->numberOfWifi = numberOfWifi;
}

void Player::setLoadedDice(){
	delete dice;
	dice = new LoadedDiceStrategy();
}

void Player::setFairDice(){
	delete dice;
	dice = new FairDiceStrategy();
}

void Player::clear(){
	numberOfBricks = 0;
	numberOfEnergy = 0;
	numberOfHeat = 0;
	numberOfGlass = 0;
	numberOfWifi = 0;

	this->addresses.clear();
	this->paths.clear();
	this->distributedResources.clear();

	delete dice;
	dice = new LoadedDiceStrategy();
}