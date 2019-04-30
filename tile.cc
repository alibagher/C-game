#include "tile.h"

Tile::Tile(int tileNumber, std::string tileName, int tileValue)
	:tileNumber{tileNumber}, tileName{tileName}, tileValue{tileValue},
	geese{false}{}

void Tile::giveResources(){
	if (this->geese){
		return;
	}

	notifyObservers();
}

int Tile::getTileNumber(){
	return this->tileNumber;
}

std::string Tile::getTileName(){
	return this->tileName;
}

int Tile::getTileValue(){
	return this->tileValue;
}

bool Tile::hasGeese(){
	return this->geese;
}

void Tile::removeGeese(){
	this->geese = false;
}
		
void Tile::setGeese(){
	this->geese = true;
}

void Tile::setTileNumber(int tileNumber){
	this->tileNumber = tileNumber;
}

void Tile::setTileValue(int tileValue){
	this->tileValue = tileValue;
}

void Tile::notifyObservers(){
	for (auto ob : this->getObservers()){
		ob->notify(*this);
	}
}