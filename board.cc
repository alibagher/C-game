#include <iomanip>
#include <string>
#include "board.h"
#include "tile.h"
#include "address.h"
#include "path.h"

const int Board::numberOfTiles = 19;
const int Board::numberOfAddresses = 54;
const int Board::numberOfPaths = 72;

const int Board::boardHeight = 21;
const int Board::boardWidth = 11;

Board::Board():tileArray{nullptr}, addressArray{nullptr}, pathArray{nullptr},
	geeseTile{-1}{
	for (int i = 0; i < numberOfAddresses; ++i){
		this->addresses.emplace_back(new Address(i));
	}

	for (int i = 0; i < numberOfPaths; ++i){
		this->paths.emplace_back(new Path(i));
	}

	this->tileArray = new Tile**[boardHeight];

	/* Initialize the tile 2d array. */
	for (int i = 0; i < boardHeight; ++i){
		this->tileArray[i] = new Tile*[boardWidth];
		for (int j = 0; j < boardWidth; ++j){
			this->tileArray[i][j] = nullptr;
		}
	}

	/* Initialize the address 2d array. */
	this->addressArray = new Address**[boardHeight];

	for (int i = 0; i < boardHeight; ++i){
		this->addressArray[i] = new Address*[boardWidth];
		for (int j = 0; j < boardWidth; ++j){
			this->addressArray[i][j] = nullptr;
		}
	}

	/* Initialize the path 2d array. */	
	this->pathArray = new Path**[boardHeight];

	for (int i = 0; i < boardHeight; ++i){
		this->pathArray[i] = new Path*[boardWidth];
		for (int j = 0; j < boardWidth; ++j){
			this->pathArray[i][j] = nullptr;
		}
	}
}

Board::~Board(){
	for (int i = 0; i < numberOfTiles; ++i){
		delete this->tiles[i];
	}

	for (int i = 0; i < numberOfAddresses; ++i){
		delete this->addresses[i];
	}

	for (int i = 0; i < numberOfPaths; ++i){
		delete this->paths[i];
	}

	for (int i = 0; i < boardHeight; ++i){
		delete [] this->pathArray[i];
		delete [] this->addressArray[i];
		delete [] this->tileArray[i];
	}

	delete [] this->pathArray;
	delete [] this->addressArray;
	delete [] this->tileArray;
}

void Board::initBoard(){
	initTileArray();
	initAddressArray();
	initPathArray();
	initTileObservers();
	initAddressObservers();
	initPathObservers();
}

void Board::clear(){
	for (int i = 0; i < numberOfAddresses; ++i){
		this->addresses[i]->clear();
	}

	for (int i = 0; i < numberOfPaths; ++i){
		this->paths[i]->clear();
	}	
}

void Board::getTileIndex(int tileNumber, int &row, int &col){
	int x, y;

	switch(tileNumber){
		case 0:
			x = 4;
			y = 0;
			break;
		case 18:
			x = 4;
			y = 16;
			break;
		default:
			x = 2;
			y = 2;
			
			for (int i = 1; i < tileNumber; ++i){
				x += 4;	
				
				if (x >= 10){
					y += 2;
				}

				x = x % 10;
			}

			break;
	}

	col = x;
	row = y;
}

bool Board::validIndexes(int row, int col) const {
	if (row < 0 || row > (boardHeight - 1) || 
		col < 0 || col > (boardWidth - 1)){
		return false;
	}

	return true;
}

void Board::initTileArray(){
	for (int i = 0; i < numberOfTiles; ++i){
		int row = 0;
		int col = 0;
		getTileIndex(i, row, col);

		this->tileArray[row][col] = this->tiles.at(i);
	}

	#ifdef DEBUG
	std::cerr << "Initialized tileArray." << std::endl;
	for (int i = 0; i < boardHeight; ++i){
		for (int j = 0; j < boardWidth; ++j){
			if (this->tileArray[i][j]){
				std::cerr << "(" << j << "," << i << ")";
			} else {
				std::cerr << "      ";
			}
		}
		std::cerr << std::endl;
	}
	#endif
}

void Board::initTileObservers(){
	/* Attach surrounding addresses to tile as observers. */
	for (int i = 0; i < numberOfTiles; ++i){
		int row = 0;
		int col = 0;
		getTileIndex(i, row, col);

		int topLeftR = row;
		int topLeftC = col;

		int topRightR = row;
		int topRightC = col + 2;

		int midLeftR = row + 2;
		int midLeftC = col;

		int midRightR = row + 2;
		int midRightC = col + 2;

		int bottomLeftR = row + 4;
		int bottomLeftC = col;

		int bottomRightR = row + 4;
		int bottomRightC = col + 2;

		this->tileArray[row][col]
			->attach(this->addressArray[topLeftR][topLeftC]);

		if (validIndexes(topRightR, topRightC)){
			this->tileArray[row][col]
				->attach(this->addressArray[topRightR][topRightC]);
		}

		if (validIndexes(midLeftR, midLeftC)){
			this->tileArray[row][col]
				->attach(this->addressArray[midLeftR][midLeftC]);
		}

		if (validIndexes(midRightR, midRightC)){
			this->tileArray[row][col]
				->attach(this->addressArray[midRightR][midRightC]);
		}

		if (validIndexes(bottomLeftR, bottomLeftC)){
			this->tileArray[row][col]
				->attach(this->addressArray[bottomLeftR][bottomLeftC]);
		}

		if (validIndexes(bottomRightR, bottomRightC)){
			this->tileArray[row][col]
				->attach(this->addressArray[bottomRightR][bottomRightC]);
		}
	}
}

void Board::initAddressArray(){
	int addressIndex = 0;

	for (int row = 0; row < boardHeight; ++row){
		for (int col = 0; col < boardWidth; ++col){
			int topRightR = row;
			int topRightC = col - 2;

			int middleLeftR = row - 2;
			int middleLeftC = col;

			int middleRightR = row - 2;
			int middleRightC = col - 2;

			int bottomLeftR = row - 4;
			int bottomLeftC = col;

			int bottomRightR = row - 4;
			int bottomRightC = col - 2;

			bool valid = false;

			if (this->tileArray[row][col]){
				valid = true;
			}
		
			if (validIndexes(topRightR, topRightC) && 
				this->tileArray[topRightR][topRightC]){
				valid = true;
			}		
			
			if (validIndexes(middleLeftR, middleLeftC) && 
				this->tileArray[middleLeftR][middleLeftC]){
				valid = true;
			}

			if (validIndexes(middleRightR, middleRightC) && 
				this->tileArray[middleRightR][middleRightC]){
				valid = true;
			}

			if (validIndexes(bottomLeftR, bottomLeftC) && 
				this->tileArray[bottomLeftR][bottomLeftC]){
				valid = true;
			}

			if (validIndexes(bottomRightR, bottomRightC) && 
				this->tileArray[bottomRightR][bottomRightC]){
				valid = true;
			}

			if (row % 2 == 0 && col % 2 == 0 && valid){
				this->addressArray[row][col] = this->addresses[addressIndex++];				
			}
		}
	}

	#ifdef DEBUG
	if (addressIndex != numberOfAddresses){
		std::cerr << "ERROR: Board::initAddressArray" << std::endl;
		std::cerr << "addressIndex: " << addressIndex << std::endl;
	} else {
		std::cerr << "Initialized addressArray." << std::endl;
		for (int i = 0; i < boardHeight; ++i){
			for (int j = 0; j < boardWidth; ++j){
				if (this->addressArray[i][j]){
					std::cerr << *(this->addressArray[i][j]);
				} else {
					std::cerr << "      ";
				}
			}
			std::cerr << std::endl;
		}
	}
	#endif
}

void Board::initAddressObservers(){
	/* Attach surrounding paths and addresses as observers. */
	for (int row = 0; row < boardHeight; ++row){
		for (int col = 0; col < boardWidth; ++col){
			if (addressArray[row][col]){
				int northR = row - 1;
				int northC = col;

				int southR = row + 1;
				int southC = col;

				int westR = row;
				int westC = col - 1;

				int eastR = row;
				int eastC = col + 1;

				if (validIndexes(northR, northC) 
					&& this->pathArray[northR][northC]){
					int northAdrR = row - 2;
					int northAdrC = col;

					if (validIndexes(northAdrR, northAdrC) 
						&& this->addressArray[northAdrR][northAdrC]){
						this->addressArray[row][col]
							->attach(this->addressArray[northAdrR][northAdrC]);
					}

					this->addressArray[row][col]
						->attach(this->pathArray[northR][northC]);
				}

				if (validIndexes(southR, southC) 
					&& this->pathArray[southR][southC]){
					int southAdrR = row + 2;
					int southAdrC = col;

					if (validIndexes(southAdrR, southAdrC) 
						&& this->addressArray[southAdrR][southAdrC]){
						this->addressArray[row][col]
							->attach(this->addressArray[southAdrR][southAdrC]);
					}

					this->addressArray[row][col]
						->attach(this->pathArray[southR][southC]);
				}

				if (validIndexes(westR, westC) 
					&& this->pathArray[westR][westC]){
					int westAdrR = row;
					int westAdrC = col - 2;

					if (validIndexes(westAdrR, westAdrC) 
						&& this->addressArray[westAdrR][westAdrC]){
						this->addressArray[row][col]
							->attach(this->addressArray[westAdrR][westAdrC]);
					}

					this->addressArray[row][col]
						->attach(this->pathArray[westR][westC]);
				}

				if (validIndexes(eastR, eastC) 
					&& this->pathArray[eastR][eastC]){
					int eastAdrR = row;
					int eastAdrC = col + 2;

					if (validIndexes(eastAdrR, eastAdrC) 
						&& this->addressArray[eastAdrR][eastAdrC]){
						this->addressArray[row][col]
							->attach(this->addressArray[eastAdrR][eastAdrC]);
					}

					this->addressArray[row][col]
						->attach(this->pathArray[eastR][eastC]);
				}			
			}
		}
	}
}

void Board::initPathArray(){
	int pathIndex = 0;

	for (int row = 0; row < boardHeight; ++row){
		for (int col = 0; col < boardWidth; ++col){
			/* Check if path exists on tile */
			int topR = row;
			int topC = col - 1;

			int topMidLeftR = row - 1;
			int topMidLeftC = col;

			int topMidRightR = row - 1;
			int topMidRightC = col - 2;

			int bottomMidLeftR = row - 3;
			int bottomMidLeftC = col;

			int bottomMidRightR = row - 3;
			int bottomMidRightC = col - 2;

			int bottomR = row - 4;
			int bottomC = col - 1;

			bool valid = false;
		
			if (validIndexes(topR, topC) && 
				this->tileArray[topR][topC]){
				valid = true;
			}
			
			if (validIndexes(topMidLeftR, topMidLeftC) && 
				this->tileArray[topMidLeftR][topMidLeftC]){
				valid = true;
			}

			if (validIndexes(topMidRightR, topMidRightC) 
				&& this->tileArray[topMidRightR][topMidRightC]){
				valid = true;
			}

			if (validIndexes(bottomMidLeftR, bottomMidLeftC) 
				&& this->tileArray[bottomMidLeftR][bottomMidLeftC]){
				valid = true;
			}

			if (validIndexes(bottomMidRightR, bottomMidRightC) 
				&& this->tileArray[bottomMidRightR][bottomMidRightC]){
				valid = true;
			}

			if (validIndexes(bottomR, bottomC) 
				&& this->tileArray[bottomR][bottomC]){
				valid = true;
			}

			if (((row % 2 == 1 && col % 2 == 0) || 
			    (row % 2 == 0 && col % 2 == 1)) && valid){
				this->pathArray[row][col] = this->paths[pathIndex++];
			}		
		}
	}

	#ifdef DEBUG
	if (pathIndex != numberOfPaths){
		std::cerr << "ERROR: Board::initPathArray" << std::endl;
		std::cerr << "pathIndex: " << pathIndex << std::endl;		
	} else {
		std::cerr << "Initialized pathArray." << std::endl;
		for (int i = 0; i < boardHeight; ++i){
			for (int j = 0; j < boardWidth; ++j){
				if (this->pathArray[i][j]){
					std::cerr << *(this->pathArray[i][j]);
				} else {
					std::cerr << "      ";
				}
			}
			std::cerr << std::endl;
		}
	}
	#endif
}

void Board::initPathObservers(){
	/* Attach surrounding paths and addresses as observers. */
	for (int row = 0; row < boardHeight; ++row){
		for (int col = 0; col < boardWidth; ++col){
			if (pathArray[row][col]){
				int northR = row - 1;
				int northC = col;

				int southR = row + 1;
				int southC = col;

				int westR = row;
				int westC = col - 1;

				int eastR = row;
				int eastC = col + 1;

				if (validIndexes(northR, northC) 
					&& this->addressArray[northR][northC]){
					int northPathR = northR - 1;
					int northPathC = northC;

					int westPathR = northR;
					int westPathC = northC - 1;

					int eastPathR = northR;
					int eastPathC = northC + 1;

					if (validIndexes(northPathR, northPathC) 
						&& this->pathArray[northPathR][northPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[northPathR][northPathC]);

					}


					if (validIndexes(westPathR, westPathC) 
						&& this->pathArray[westPathR][westPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[westPathR][westPathC]);
					}

					if (validIndexes(eastPathR, eastPathC) 
						&& this->pathArray[eastPathR][eastPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[eastPathR][eastPathC]);
					}

					this->pathArray[row][col]
						->attach(this->addressArray[northR][northC]);
				}

				if (validIndexes(southR, southC) 
					&& this->addressArray[southR][southC]){
					int southPathR = southR + 1;
					int southPathC = southC;

					int westPathR = southR;
					int westPathC = southC - 1;

					int eastPathR = southR;
					int eastPathC = southC + 1;

					if (validIndexes(southPathR, southPathC) 
						&& this->pathArray[southPathR][southPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[southPathR][southPathC]);
					}

					if (validIndexes(westPathR, westPathC) 
						&& this->pathArray[westPathR][westPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[westPathR][westPathC]);
					}

					if (validIndexes(eastPathR, eastPathC) 
						&& this->pathArray[eastPathR][eastPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[eastPathR][eastPathC]);
					}

					this->pathArray[row][col]
						->attach(this->addressArray[southR][southC]);
				}

				if (validIndexes(westR, westC) 
					&& this->addressArray[westR][westC]){
					int northPathR = westR - 1;
					int northPathC = westC;

					int southPathR = westR + 1;
					int southPathC = westC;

					if (validIndexes(northPathR, northPathC) 
						&& this->pathArray[northPathR][northPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[northPathR][northPathC]);
					}

					if (validIndexes(southPathR, southPathC) 
						&& this->pathArray[southPathR][southPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[southPathR][southPathC]);
					}

					this->pathArray[row][col]
						->attach(this->addressArray[westR][westC]);
				}

				if (validIndexes(eastR, eastC) 
					&& this->addressArray[eastR][eastC]){
					int northPathR = eastR - 1;
					int northPathC = eastC;

					int southPathR = eastR + 1;
					int southPathC = eastC;

					if (validIndexes(northPathR, northPathC) 
						&& this->pathArray[northPathR][northPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[northPathR][northPathC]);
					}

					if (validIndexes(southPathR, southPathC) 
						&& this->pathArray[southPathR][southPathC]){
						this->pathArray[row][col]
							->attach(this->pathArray[southPathR][southPathC]);
					}

					this->pathArray[row][col]
						->attach(this->addressArray[eastR][eastC]);
				}
			}
		}
	}
}

void Board::addTile(Tile *tile){
	#ifdef DEBUG
	if (this->tiles.size() > numberOfTiles){
		std::cerr << "ERROR: adding tile number: " << this->tiles.size();
		std::cerr << std::endl;
	}
	#endif

	this->tiles.emplace_back(tile);
}

void Board::distributeResources(int tileValue){
	for (auto it: this->tiles){
		if ((*it).getTileValue() == tileValue){
			(*it).giveResources();
		}
	}
}

bool Board::buildBasement(Player *player, int addressNum, bool init){
	if (addressNum < 0 || addressNum > (numberOfAddresses - 1)){
		return false;
	}

	bool built = this->addresses[addressNum]->build(player, init);

	if (built){
		this->addresses[addressNum]->improve();		
	}

	return built;
}

bool Board::buildRoad(Player *player, int pathNum, bool init){
	if (pathNum < 0 || pathNum > (numberOfPaths - 1)){
		return false;
	}

	return this->paths[pathNum]->build(player, init);
}

bool Board::setGeese(int tileNumber){
	if (tileNumber == this->geeseTile){
		return false;
	}

	this->tiles[tileNumber]->setGeese();

	if (this->geeseTile != -1){
		this->tiles[this->geeseTile]->removeGeese();
	}

	this->geeseTile = tileNumber;
	
	return true;
}

std::vector<Address*> Board::getSurroundingAddresses(int tileNumber){
	std::vector<Address*> addrs;

	int row = 0;
	int col = 0;
	getTileIndex(tileNumber, row, col);

	int topLeftR = row;
	int topLeftC = col;

	int topRightR = row;
	int topRightC = col + 2;

	int midLeftR = row + 2;
	int midLeftC = col;

	int midRightR = row + 2;
	int midRightC = col + 2;

	int bottomLeftR = row + 4;
	int bottomLeftC = col;

	int bottomRightR = row + 4;
	int bottomRightC = col + 2;

	addrs.emplace_back(this->addressArray[topLeftR][topLeftC]);

	if (validIndexes(topRightR, topRightC)){
		addrs.emplace_back(this->addressArray[topRightR][topRightC]);
	}

	if (validIndexes(midLeftR, midLeftC)){
		addrs.emplace_back(this->addressArray[midLeftR][midLeftC]);
	}

	if (validIndexes(midRightR, midRightC)){
		addrs.emplace_back(this->addressArray[midRightR][midRightC]);
	}

	if (validIndexes(bottomLeftR, bottomLeftC)){
		addrs.emplace_back(this->addressArray[bottomLeftR][bottomLeftC]);
	}

	if (validIndexes(bottomRightR, bottomRightC)){
		addrs.emplace_back(this->addressArray[bottomRightR][bottomRightC]);
	}

	return addrs;
}

void Board::printSaveFormat(std::ostream &out) const {
	for (auto it: this->tiles){
		(*it).printSaveFormat(out);
		out << " ";
	}
}

std::ostream &operator<<(std::ostream &out, const Board &board){
	for (int row = 0; row < Board::boardHeight; ++row){
		/* Various spaces for pretty printing board. */
		if (row == 0 || (row == Board::boardHeight - 1)){
			out << "  ";
		} else if (row == 2 || (row == Board::boardHeight - 3)){
			out << " ";
		}

		for (int col = 0; col < Board::boardWidth; ++col){
			/* Printing an address. */
			if (row % 2 == 0 && col % 2 == 0){
				if (board.addressArray[row][col]){
					out << *(board.addressArray[row][col]);
				} else {
					out << "   ";
				}
			/* Printing a horizontal path. */
			} else if (row % 2 == 0 && col % 2 == 1){
				if (board.pathArray[row][col]){
					out << "--" << *(board.pathArray[row][col]) << "--";
				} else {
					int tileRowIndex = row - 2;
					int tileColIndex = col - 1;

					if (board.validIndexes(tileRowIndex, tileColIndex) && 
						board.tileArray[tileRowIndex][tileColIndex]){
						out << std::setw(4);

						std::string name = board
								.tileArray[tileRowIndex][tileColIndex]
								->getTileName();

						if (name == "PARK"){
							out << " ";
						} else {
							out << board.tileArray[tileRowIndex][tileColIndex]
								->getTileValue();
						}

						out << "  ";
					} else {
						out << "      ";
					}
				}
			/* Printing a vertical path. */
			} else if (row % 2 == 1 && col % 2 == 0){
				/* Printing |...| for tiles. */
				for (int j = 0; j < Board::boardWidth; ++j){
					bool valid = false;

					if (board.pathArray[row][j]){
						valid = true;
					}

					if (j % 2 == 0){
						if (valid){
							out << std::setw(3) << "|";
						} else {
							out << "   ";
						}
					} else {
						/* If printing tile with geese */
						if (board.validIndexes(row - 3, j - 1) 
							&& board.tileArray[row - 3][j - 1]
							&& board.tileArray[row - 3][j - 1]->hasGeese()){
							out << "  GEESE";
						/* Otherwise, printing with no geese */
						} else {
							out << "       ";
						}
					}
				}

				out << std::endl;

				/* Printing paths for tiles. */
				for (int j = 0; j < Board::boardWidth; ++j){
					bool valid = false;

					if (board.pathArray[row][j]){
						valid = true;
					}

					if (j % 2 == 0){
						if (valid){
							out << " " << *(board.pathArray[row][j]);
						} else {
							out << "   ";
						}
					} else {
						/* If printing row with tileNumber */
						if (board.validIndexes(row - 1, j - 1) 
							&& board.tileArray[row - 1][j - 1]){
							out << std::setw(5);
							out << board.tileArray[row - 1][j - 1]
								->getTileNumber();
							out << "  ";
						/* Otherwise, printing with no tileNumber */
						} else {
							out << "       ";
						}
					}
				}

				out << std::endl;

				/* Printing |.<ENERGY>.| for tiles. */

				for (int j = 0; j < Board::boardWidth; ++j){
					bool valid = false;

					if (board.pathArray[row][j]){
						valid = true;
					}

					if (j % 2 == 0){
						if (valid){
							out << std::setw(3) << "|";
						} else {
							out << "   ";
						}
					} else {
						/* If printing row with tileName */
						if (board.validIndexes(row - 1, j - 1) 
							&& board.tileArray[row - 1][j - 1]){
							std::string name = board.tileArray[row - 1][j - 1]
								->getTileName();
							out << "  " << name;

							/* Add spacing for pretty print. */
							int spacing = 5 - name.length();
							if (spacing >= 0){
								for (int i = 0; i < spacing; ++i){
									out << " ";
								}
							} else {
								out << " |";
								++j;
							}
						/* Otherwise, printing with no tileName */
						} else {
							out << "       ";
						}
					}
				}

				break;
			}
		}

		out << std::endl;
	}

	return out;
}