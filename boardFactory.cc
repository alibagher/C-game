#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "boardFactory.h"
#include "brick.h"
#include "energy.h"
#include "glass.h"
#include "heat.h"
#include "park.h"
#include "wifi.h"

Board *BoardFactory::makeBoard(std::istream &in){
	Board *board = new Board();

	int tileNumber = 0;
	int tileNameInt = 0;
	int tileValue = 0;

	/* Iterate through all tiles. */
	for (int i = 0; i < 19; ++i){
		in >> tileNameInt;
		in >> tileValue;

		Tile *tile = nullptr;

		switch (tileNameInt){
			case 0:
				tile = new Brick(tileNumber, tileValue);
				break;
			case 1:
				tile = new Energy(tileNumber, tileValue);
				break;
			case 2:
				tile = new Glass(tileNumber, tileValue);			
				break;
			case 3:
				tile = new Heat(tileNumber, tileValue);
				break;
			case 4:
				tile = new Wifi(tileNumber, tileValue);			
				break;
			case 5:
				tile = new Park(tileNumber);
				break;
		}

		board->addTile(tile);
		++tileNumber;
	}

	board->initBoard();	

	return board;
}

/*
  On random generation, board will consist of 3 Wifi, 3 heat, 4 Brick,
  4 Energy, 4 Glass and 1 Park. The distribution will be:
  One tile with value 2
  Two tiles with value 3-6
  Two tiles with value 8-11
  One tile with value 12
*/
Board *BoardFactory::makeRandomBoard(int seed){
	Board *board = new Board();
	std::vector<Tile*> tiles;

	tiles.emplace_back(new Wifi(0, 0));
	tiles.emplace_back(new Wifi(0, 0));
	tiles.emplace_back(new Wifi(0, 0));

	tiles.emplace_back(new Heat(0, 0));
	tiles.emplace_back(new Heat(0, 0));
	tiles.emplace_back(new Heat(0, 0));

	tiles.emplace_back(new Brick(0, 0));
	tiles.emplace_back(new Brick(0, 0));
	tiles.emplace_back(new Brick(0, 0));
	tiles.emplace_back(new Brick(0, 0));

	tiles.emplace_back(new Energy(0, 0));
	tiles.emplace_back(new Energy(0, 0));
	tiles.emplace_back(new Energy(0, 0));
	tiles.emplace_back(new Energy(0, 0));

	tiles.emplace_back(new Glass(0, 0));
	tiles.emplace_back(new Glass(0, 0));
	tiles.emplace_back(new Glass(0, 0));
	tiles.emplace_back(new Glass(0, 0));

	tiles.emplace_back(new Park(0));

	srand(time(0));

	/* Randomly sort the tiles. */
	std::random_shuffle(tiles.begin(), tiles.end());

	tiles[0]->setTileValue(2);

	tiles[1]->setTileValue(3);
	tiles[2]->setTileValue(3);
	tiles[3]->setTileValue(4);
	tiles[4]->setTileValue(4);
	tiles[5]->setTileValue(5);
	tiles[6]->setTileValue(5);
	tiles[7]->setTileValue(6);
	tiles[8]->setTileValue(6);

	tiles[9]->setTileValue(8);
	tiles[10]->setTileValue(8);
	tiles[11]->setTileValue(9);
	tiles[12]->setTileValue(9);
	tiles[13]->setTileValue(10);
	tiles[14]->setTileValue(10);
	tiles[15]->setTileValue(11);
	tiles[16]->setTileValue(11);

	tiles[17]->setTileValue(12);

	srand(seed);

	/* Randomly sort the tiles again. */
	std::random_shuffle(tiles.begin(), tiles.end());

	int tileNumber = 0;
	int i = 0;

	for (auto &it: tiles){
		(*it).setTileNumber(tileNumber++);
		board->addTile(&*it);
		++i;
	}

	#ifdef DEBUG
	if (tileNumber != 19){
		std::cerr << "ERROR: Making Random board does not iterate correctly.";
		std::cerr << std::endl;
	}
	#endif

	board->initBoard();

	return board;
}