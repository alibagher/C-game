#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "board.h"
#include "boardFactory.h"
#include "bluePlayer.h"
#include "redPlayer.h"
#include "orangePlayer.h"
#include "yellowPlayer.h"

Player *won(){
	if (BluePlayer::getInstance()->getPoints() >= 10){
		return BluePlayer::getInstance();
	} else if (RedPlayer::getInstance()->getPoints() >= 10){
		return RedPlayer::getInstance();
	} else if (OrangePlayer::getInstance()->getPoints() >= 10){
		return OrangePlayer::getInstance();
	} else if (YellowPlayer::getInstance()->getPoints() >= 10){
		return YellowPlayer::getInstance();
	} else {
		return nullptr;
	}
}

bool initPlayerData(Board &board, Player *player, std::string builderData){
	std::istringstream iss {builderData};
	int resources = 0;

	iss >> resources;
	player->setNumberOfBricks(resources);

	iss >> resources;
	player->setNumberOfEnergy(resources);			

	iss >> resources;
	player->setNumberOfGlass(resources);

	iss >> resources;
	player->setNumberOfHeat(resources);

	iss >> resources;
	player->setNumberOfWifi(resources);

	std::string r;
	iss >> r;

	if (r != "r"){
		return false;
	}

	int pathValue;

	while (iss >> pathValue){
		board.buildRoad(player, pathValue, true);
	}

	std::string h;
	iss.clear();
	iss >> h;

	if (h != "h"){
		return false;
	}

	std::string residence;
	int addressValue;

	while (iss >> addressValue && iss >> residence){
		board.buildBasement(player, addressValue, true);

		if (residence == "H"){
			player->improve(board, addressValue);
		} else if (residence == "T"){
			player->improve(board, addressValue);
			player->improve(board, addressValue);
		}
	}

	return true;
}

void initPlayerBasements(Board &board){
	std::vector<Player*> initPlayers{BluePlayer::getInstance(), 
		RedPlayer::getInstance(), OrangePlayer::getInstance(),
		YellowPlayer::getInstance()};

	initPlayers.insert(initPlayers.end(), 
		initPlayers.rbegin(), initPlayers.rend());

	for (auto it: initPlayers){
		int addressValue = 0;

		std::cout << "Builder " << (*it).getName();
		std::cout << ", where do you want to build a basement?" << std::endl;
		
		while (true){
			std::cout << "> ";

			std::string addressVal;
			std::cin >> addressVal;

			std::istringstream iss {addressVal};

			if (!(iss >> addressValue)){
				std::cerr << "You cannot build here." << std::endl;
				continue;
			}

			bool built = board.buildBasement(it, addressValue, true);

			if (built){
				break;
			} else {
				std::cerr << "You cannot build here." << std::endl;
			}
		}
	}
}

void handleGeese(Board &board, Player *activePlayer){
	std::vector<Player*> players{BluePlayer::getInstance(), 
		RedPlayer::getInstance(), OrangePlayer::getInstance(),
		YellowPlayer::getInstance()};

	for (auto p: players){
		(*p).loseResources();
	}

	int geeseTileNumber;
	std::string input;
	std::cout << "Choose where to place the GEESE." << std::endl;

	while (std::cout << "> " && std::cin >> input){
		std::istringstream iss {input};

		if (!(iss >> geeseTileNumber)){
			std::cerr << "Invalid command." << std::endl;
			continue;
		}

		bool set = board.setGeese(geeseTileNumber);

		if (!set){
			std::cerr << "Select different tile location.";
			std::cerr << std::endl;
		} else {
			break;
		}
	}

	std::vector<Player*> stealablePlayers;

	for (auto addressIt: board.getSurroundingAddresses(geeseTileNumber)){
		Player *p = (*addressIt).getOwner(); 
		if (p && p->getTotalResources() != 0 && p != activePlayer){
			bool valid = true;

			/* If player already exists, no need to add them again. */
			for (auto player: stealablePlayers){
				if (player == p){
					valid = false;
					break;
				}
			}

			if (valid) stealablePlayers.emplace_back(p);
		}
	}

	if (stealablePlayers.size() == 0){
		std::cout << "Builder " << (activePlayer)->getName();
		std::cout << " has no builders to steal from.";
		std::cout << std::endl;
	} else {
		std::cout << "Builder " << (activePlayer)->getName();
		std::cout << " can choose to steal from ";

		/* Used to print in order of builder 0, 1, 2, 3. */
		for (unsigned i = 0; i < players.size(); ++i){
			for (unsigned j = 0; j < stealablePlayers.size(); ++j){
				if (players[i] == stealablePlayers[j] 
					&& stealablePlayers[j] != activePlayer){
					std::cout << players[i]->getName();
					if ((i + 1) < stealablePlayers.size()){
						std::cout << ", ";
					}

					break;
				}
			}
		}

		std::cout << "." << std::endl;
		std::cout << "Choose a builder to steal from.";
		std::cout << std::endl;

		std::string stealFrom, stolen;

		while (std::cout << "> " && std::cin >> stealFrom){
			if (stealFrom == "Blue"){
				stolen = BluePlayer::getInstance()->steal(activePlayer);
				std::cout << "Builder " << (activePlayer)->getName();
				std::cout << " steals " << stolen;
				std::cout << " from builder Blue." << std::endl;
				break;
			} else if (stealFrom == "Red"){	
				stolen = RedPlayer::getInstance()->steal(activePlayer);
				std::cout << "Builder " << (activePlayer)->getName();
				std::cout << " steals " << stolen;
				std::cout << " from builder Red." << std::endl;
				break;
			} else if (stealFrom == "Yellow"){
				stolen = YellowPlayer::getInstance()->steal(activePlayer);
				std::cout << "Builder " << (activePlayer)->getName();
				std::cout << " steals " << stolen;
				std::cout << " from builder Yellow." << std::endl;
				break;	
			} else if (stealFrom == "Orange"){	
				stolen = OrangePlayer::getInstance()->steal(activePlayer);
				std::cout << "Builder " << (activePlayer)->getName();
				std::cout << " steals " << stolen;
				std::cout << " from builder Orange." << std::endl;
				break;
			} else {
				std::cerr << "Invalid command." << std::endl;
				continue;
			}
		}
	}	
}

void handleTrade(Board &board, Player *buyer, Player *seller, 
	std::string give, std::string take){
	std::cout << buyer->getName() << " offers " << seller->getName();
	std::cout << " one " << give <<  " for one " << take << ".";
	std::cout << std::endl;

	std::cout << "Does " << seller->getName() << " accept this offer?";
	std::cout << std::endl;

	std::string ans;

	while (std::cout << "> " && std::cin >> ans){
		if (ans == "yes"){
			if (give == "brick"){
				buyer->setNumberOfBricks(buyer->getNumberOfBricks() - 1);
				seller->setNumberOfBricks(seller->getNumberOfBricks() + 1);

			} else if(give == "energy"){
				buyer->setNumberOfEnergy(buyer->getNumberOfEnergy() - 1);
				seller->setNumberOfEnergy(seller->getNumberOfEnergy() + 1);

			} else if(give == "glass"){
				buyer->setNumberOfGlass(buyer->getNumberOfGlass() - 1);
				seller->setNumberOfGlass(seller->getNumberOfGlass() + 1);

			} else if(give == "heat"){
				buyer->setNumberOfHeat(buyer->getNumberOfHeat() - 1);
				seller->setNumberOfHeat(seller->getNumberOfHeat() + 1);

			} else if(give == "wifi"){
				buyer->setNumberOfWifi(buyer->getNumberOfWifi() - 1);
				seller->setNumberOfWifi(seller->getNumberOfWifi() + 1);
			}

			if (take == "brick"){
				buyer->setNumberOfBricks(buyer->getNumberOfBricks() + 1);
				seller->setNumberOfBricks(seller->getNumberOfBricks() - 1);

			} else if(take == "energy"){
				buyer->setNumberOfEnergy(buyer->getNumberOfEnergy() + 1);
				seller->setNumberOfEnergy(seller->getNumberOfEnergy() - 1);

			} else if(take == "glass"){
				buyer->setNumberOfGlass(buyer->getNumberOfGlass() + 1);
				seller->setNumberOfGlass(seller->getNumberOfGlass() - 1);

			} else if(take == "heat"){
				buyer->setNumberOfHeat(buyer->getNumberOfHeat() + 1);
				seller->setNumberOfHeat(seller->getNumberOfHeat() - 1);

			} else if(take == "wifi"){
				buyer->setNumberOfWifi(buyer->getNumberOfWifi() + 1);
				seller->setNumberOfWifi(seller->getNumberOfWifi() - 1);
			}

			break;
		} else if (ans == "no"){
			break;
		} else {
			std::cerr << "Invalid command." << std::endl;
		}
	}	
}

void runGame(Board &board, int currentTurn){
	std::vector<Player*> players{BluePlayer::getInstance(), 
		RedPlayer::getInstance(), OrangePlayer::getInstance(),
		YellowPlayer::getInstance()};

	std::vector<Player*>::iterator it = players.begin();
	std::string input;

	while (!won() && !std::cin.eof()){
		std::cout << "Builder " << (*it)->getName() << "'s turn." << std::endl;
		(*it)->printStatus(std::cout);
		std::cout << std::endl;

		std::string typeOfDice;

		std::cout << "Please enter the type of dice." << std::endl;
		while (std::cout << "> " && std::cin >> typeOfDice){
			if (typeOfDice == "load"){
				(*it)->setLoadedDice();
			} else if (typeOfDice == "fair"){
				(*it)->setFairDice();
			} else if (typeOfDice == "roll"){
				int roll = (*it)->rollDice();

				if (roll != 7){
					for (auto playerIt: players){
						(*playerIt).clearDistributedResources();					
					}

					board.distributeResources(roll);

					bool anyoneDistributed = false;

					for (auto playerIt: players){
						auto resources = (*playerIt).getDistributedResources();

						if (resources.size() > 0){
							anyoneDistributed = true;
							std::cout << "Builder " << (*playerIt).getName();
							std::cout << " gained:" << std::endl;				
						}

						for (auto resource: resources){
							if (resource.second > 0){
								std::cout << resource.second << " ";
								std::cout << resource.first << std::endl;
							}
						}
					}

					if (!anyoneDistributed){
						std::cout << "No builders gained resources.";
						std::cout << std::endl;
					}					
				} else {
					handleGeese(board, *it);
				}

				break;
			} else {
				std::cerr << "Invalid command." << std::endl;
			}
		}

		while (std::cout << "> " && std::cin >> input 
			&& input != "next" && !won()){
			if (input == "board"){
				std::cout << board << std::endl;
			} else if (input == "status"){
				for (auto i: players){
					(*i).printStatus(std::cout);
					std::cout << std::endl;
				}
			} else if (input == "residences"){
				(*it)->printResidences(std::cout);
			} else if (input == "build-road"){
				int roadNum = 0;
				std::string inp;
				while(std::cin >> inp){
					std::istringstream ss{inp};
					if (!(ss >> roadNum)){
						std::cerr << "You cannot build here." << std::endl;
					}else{
						break;
					}
				}

				if ((*it)->getNumberOfHeat() < 1 
					|| (*it)->getNumberOfWifi() < 1){
					std::cerr << "You do not have enough resources.";
					std::cerr << std::endl;
					continue;
				}

				bool built = board.buildRoad(*it, roadNum);

				if (built){
					(*it)->setNumberOfWifi((*it)->getNumberOfWifi() - 1);
					(*it)->setNumberOfHeat((*it)->getNumberOfHeat() - 1);						
				} else {
					std::cerr << "You cannot build here." << std::endl;
				}
			} else if (input == "build-res"){
				int addressNum = 0;

				std::string inp;
				while (std::cin >> inp){
					std::istringstream ss{inp};
					if (!(ss >> addressNum)){
						std::cerr << "You cannot build here." << std::endl;
					}else{
						break;
					}
				}

				if ((*it)->getNumberOfBricks() < 1 
					|| (*it)->getNumberOfEnergy() < 1
					|| (*it)->getNumberOfGlass() < 1 
					|| (*it)->getNumberOfWifi() < 1){
					std::cerr << "You do not have enough resources.";
					std::cerr << std::endl;
					continue;
				}

				bool built = board.buildBasement(*it, addressNum);

				if (!built){
					std::cerr << "You cannot build here." << std::endl;
					continue;					
				}

				(*it)->setNumberOfBricks((*it)->getNumberOfBricks() - 1);
				(*it)->setNumberOfEnergy((*it)->getNumberOfEnergy() - 1);
				(*it)->setNumberOfGlass((*it)->getNumberOfGlass() - 1);
				(*it)->setNumberOfWifi((*it)->getNumberOfWifi() - 1);
			} else if (input == "improve"){
				int addressNum = 0;
				std::string inp;
				while(std::cin >> inp){
					std::istringstream ss{inp};
					if (!(ss >> addressNum)){
						std::cerr << "You cannot build here." << std::endl;
					}else{
						break;
					}
				}

				Address *address = (*it)->getAddress(addressNum);

				if (!address){
					std::cerr << "You cannot build here." << std::endl;
					continue;	
				}

				bool canImprove = true;

				if (address->getTypeOfAddress() == 'B'){
					if ((*it)->getNumberOfGlass() < 2 
						|| (*it)->getNumberOfHeat() < 3){
						canImprove = false;
					}
				}

				if (address->getTypeOfAddress() == 'H'){
					if ((*it)->getNumberOfBricks() < 3 
						|| (*it)->getNumberOfEnergy() < 2 
						|| (*it)->getNumberOfGlass() < 2 
						|| (*it)->getNumberOfWifi() < 1 
						|| (*it)->getNumberOfHeat() < 2){
							canImprove = false;
					}
				}

				if (!canImprove){
					std::cerr << "You do not have enough resources.";
					std::cerr << std::endl;
					continue;					
				}

				bool built = (*it)->improve(board, addressNum);

				if (!built){
					std::cerr << "You cannot build here." << std::endl;
					continue;
				}

				if (address->getTypeOfAddress() == 'H'){
					(*it)->setNumberOfGlass((*it)->getNumberOfGlass() - 2);
					(*it)->setNumberOfHeat((*it)->getNumberOfHeat() - 3);
				}

				if (address->getTypeOfAddress() == 'T'){
					(*it)->setNumberOfBricks((*it)->getNumberOfBricks() - 3);
					(*it)->setNumberOfEnergy((*it)->getNumberOfEnergy() - 2);
					(*it)->setNumberOfGlass((*it)->getNumberOfGlass() - 2);
					(*it)->setNumberOfWifi((*it)->getNumberOfWifi() - 1);
					(*it)->setNumberOfHeat((*it)->getNumberOfHeat() - 2);
				}
			} else if (input == "trade"){
				Player *p;
				std::string colour, give, take;
				std::cin >> colour >> give >> take;

				if (colour == "Red"){
					p = RedPlayer::getInstance();
				} else if(colour == "Blue"){
					p = BluePlayer::getInstance();
				} else if(colour == "Yellow"){
					p = YellowPlayer::getInstance();
				} else if(colour == "Orange"){
					p = OrangePlayer::getInstance();
				} else {
					std::cerr << "Invalid command." << std::endl;
					std::cin.ignore(256,'\n');
					continue;
				}

				if (!(give == "brick" || give == "energy" || give == "glass" 
					|| give == "heat" || give == "wifi")){
					std::cerr << "Invalid command." << std::endl;
					std::cin.ignore(256,'\n');
					continue;
				}

				if (!(take == "brick" || take == "energy" || take == "glass" 
					|| take == "heat" || take == "wifi")){
					std::cerr << "Invalid command." << std::endl;
					std::cin.ignore(256,'\n');
					continue;
				}

				bool validTrade = true;

				if (give == "brick"){
					if ((*it)->getNumberOfBricks() <= 0){
						validTrade = false;
					}
				} else if (give == "energy"){
					if ((*it)->getNumberOfEnergy() <= 0){
						validTrade = false;
					}
				} else if (give == "glass"){
					if ((*it)->getNumberOfGlass() <= 0){
						validTrade = false;
					}
				} else if (give == "heat"){
					if ((*it)->getNumberOfHeat() <= 0){
						validTrade = false;
					}
				} else if (give == "wifi"){
					if ((*it)->getNumberOfWifi() <= 0){
						validTrade = false;
					}
				}

				if (take == "brick"){
					if (p->getNumberOfBricks() <= 0){
						validTrade = false;
					}
				} else if (take == "energy"){
					if (p->getNumberOfEnergy() <= 0){
						validTrade = false;
					}
				} else if (take == "glass"){
					if (p->getNumberOfGlass() <= 0){
						validTrade = false;
					}
				} else if (take == "heat"){
					if (p->getNumberOfHeat() <= 0){
						validTrade = false;
					}
				} else if (take == "wifi"){
					if (p->getNumberOfWifi() <= 0){
						validTrade = false;
					}
				}

				if (!validTrade){
					std::cout << "You do not have enough resources.";
					std::cout << std::endl;
					continue;
				}

				handleTrade(board, *it, p, give, take);
			} else if (input == "save"){
				std::string savefile;
				std::cout << "> ";
				std::cin >> savefile;

				std::ofstream ofs {savefile};

				ofs << currentTurn << std::endl;

				for (auto builderIt: players){
					(*builderIt).printSaveFormat(ofs);
					ofs << std::endl;
				}

				board.printSaveFormat(ofs);
				ofs.close();
			} else if (input == "help"){
				std::cout << "Valid commands:" << std::endl;
				std::cout << "board" << std::endl;
				std::cout << "status" << std::endl;
				std::cout << "residences" << std::endl;
				std::cout << "build-road <path#>" << std::endl;
				std::cout << "build-res <housing#>" << std::endl;
				std::cout << "improve <housing#>" << std::endl;
				std::cout << "trade <colour> <give> <take>" << std::endl;
				std::cout << "next" << std::endl;
				std::cout << "save <file>" << std::endl;
				std::cout << "help" << std::endl;
			} else {
				std::cerr << "Invalid command." << std::endl;
			}
		}

		++currentTurn;

		if ((it + 1) == players.end()){
			it = players.begin();
		} else {
			++it;
		}

		if (!won() && !std::cin.eof()){
			std::cout << board;
		}
	}
}

int main(int argc, char* argv[]){
	int currentTurn = 1;
	Board *board;
	std::vector<Player*> players{BluePlayer::getInstance(), 
		RedPlayer::getInstance(), OrangePlayer::getInstance(),
		YellowPlayer::getInstance()};

	while (!std::cin.eof()){
		bool initGame = true;

		std::string boardLayout = "layout.txt";
		std::string savedGame = "savefile.txt";
		int seed = time(0);

		bool loadSavedGame = false;
		bool loadBoardLayout = false;
		bool generateRandomBoard = false;

		for (int i = 1; i < argc; ++i){
				std::string option = argv[i];

				if (option == "-seed"){
					if (!((i + 1) < argc)){
						std::cerr << "Invalid command." << std::endl;
						return 1;
					}

					std::istringstream iss {argv[i + 1]};

					if (!(iss >> seed)){
						std::cerr << "Invalid command." << std::endl;
						return 1;
					}
					++i;				
				} else if (option == "-load"){
					if (!((i + 1) < argc)){
						std::cerr << "Invalid command." << std::endl;
						return 1;
					}

					std::istringstream iss {argv[i + 1]};

					iss >> savedGame;
					loadSavedGame = true;
					++i;
				} else if (option == "-board"){
					if (!((i + 1) < argc)){
						std::cerr << "Invalid command." << std::endl;
						return 1;
					}

					std::istringstream iss {argv[i + 1]};

					iss >> boardLayout;
					loadBoardLayout = true;
					++i;
				} else if (option == "-random-board"){
					generateRandomBoard = true;
				} else {
					std::cerr << "Invalid command." << std::endl;
					return 1;
				}
		}

		if (loadSavedGame){
			std::ifstream ifs {savedGame};

			if (!ifs.is_open()){
				std::cerr << savedGame << " does not exist or is not readable";
				std::cerr << std::endl;
				return 1;
			}

			std::string currentTurnStr;
			std::getline(ifs, currentTurnStr);
			std::istringstream iss_turn {currentTurnStr};

			iss_turn >> currentTurn;

			std::string bluePlayerData;
			std::getline(ifs, bluePlayerData);

			std::string redPlayerData;
			std::getline(ifs, redPlayerData);

			std::string orangePlayerData;
			std::getline(ifs, orangePlayerData);

			std::string yellowPlayerData;
			std::getline(ifs, yellowPlayerData);

			std::string boardData;
			std::getline(ifs, boardData);

			std::istringstream iss {boardData};
			board = BoardFactory::makeBoard(iss);

			bool valid0Data = initPlayerData(*board, players[0], bluePlayerData);
			bool valid1Data = initPlayerData(*board, players[1], redPlayerData);
			bool valid2Data = initPlayerData(*board, players[2], orangePlayerData);
			bool valid3Data = initPlayerData(*board, players[3], yellowPlayerData);

			if (!valid0Data || !valid1Data || !valid2Data || !valid3Data){
				std::cerr << "Invalid save file format." << std::endl;
				return 1;
			}

			initGame = false;
		} else if (loadBoardLayout){
			std::ifstream ifs {boardLayout};

			if (!ifs.is_open()){
				std::cerr << boardLayout << " does not exist or is not readable";
				std::cerr << std::endl;
				return 1;
			}

			board = BoardFactory::makeBoard(ifs);
		} else if (generateRandomBoard){
			board = BoardFactory::makeRandomBoard(seed);
		} else {
			std::ifstream ifs {boardLayout};
			boardLayout = "layout.txt";

			if (!ifs.is_open()){
				std::cerr << boardLayout << " does not exist or is not readable";
				std::cerr << std::endl;
				return 1;
			}

			board = BoardFactory::makeBoard(ifs);
		}

		std::cout << *board << std::endl;

		if (initGame){
			initPlayerBasements(*board);
		}

		runGame(*board, currentTurn);

		if (won() && !std::cin.eof()){
			std::cout << "Would you like to play again?" << std::endl;
			std::string input;

			while (std::cout << "> " && std::cin >> input){
				if (input == "yes"){
					break;
				} else if (input == "no"){
					delete board;
					return 0;
				} else {
					std::cerr << "Invalid command." << std::endl;
				}
			}
		}

		for (auto it: players){
			(*it).clear();
		}

		(*board).clear();
	}

	if (std::cin.eof()){
		std::ofstream ofs {"backup.sv"};

		ofs << currentTurn << std::endl;

		for (auto builderIt: players){
			(*builderIt).printSaveFormat(ofs);
			ofs << std::endl;
		}

		(*board).printSaveFormat(ofs);
		ofs.close();		
	}

	delete board;
}