#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "player.h"

class Tile;
class Address;
class Path;

class Board {
	static const int numberOfTiles;
	static const int numberOfAddresses;
	static const int numberOfPaths;

	static const int boardHeight;
	static const int boardWidth;

	std::vector<Tile*> tiles;
	std::vector<Address*> addresses;
	std::vector<Path*> paths;

	Tile ***tileArray;
	Address ***addressArray;
	Path ***pathArray;

	int geeseTile;

	void getTileIndex(int tileNumber, int &row, int &col);
	bool validIndexes(int row, int col) const;
	void initTileArray();
	void initAddressArray();
	void initPathArray();
	void initTileObservers();
	void initAddressObservers();
	void initPathObservers();

	public:
		Board();
		~Board();

		void initBoard();
		void clear();
		void addTile(Tile *tile);

		void distributeResources(int tileValue);

		bool buildBasement(Player *player, int addressNum, bool init = false);
		bool buildRoad(Player *player, int pathNum, bool init = false);

		std::vector<Address*> getSurroundingAddresses(int tileNumber);
		bool setGeese(int tileNumber);

		void printSaveFormat(std::ostream &out) const;

	friend std::ostream &operator<<(std::ostream &out, const Board &board);
};

#endif
