#include "constructable.h"
#include "bluePlayer.h"
#include "redPlayer.h"
#include "orangePlayer.h"
#include "yellowPlayer.h"

Constructable::Constructable(): owner{nullptr}, buildable{true}{}

void Constructable::clear(){
	this->owner = nullptr;
	this->buildable = true;
	this->playersThatCanBuild.clear();
}

bool Constructable::canPlayerBuild(Player *player){
	if (!this->buildable){
		return false;
	}

	for (auto it = playersThatCanBuild.begin(); 
		it != playersThatCanBuild.end(); ++it){
		if (*it == player){
			return true;
		}
	}

	return false;
}

void Constructable::setPlayerCanBuild(Player *player){
	if (!this->buildable){
		return;
	}

	for (auto it = playersThatCanBuild.begin(); 
		it != playersThatCanBuild.end(); ++it){
		if (*it == player){
			return;
		}
	}

	playersThatCanBuild.emplace_back(player);
}

void Constructable::setUnBuildable(){
	this->playersThatCanBuild.clear();
	this->buildable = false;
}

bool Constructable::build(Player *player, bool init){
	if (!this->owner && this->buildable){
		if (init || canPlayerBuild(player)){
			this->owner = player;
			this->doBuild();
			this->notifyObservers();

			return true;
		}
	}

	return false;
}

Player *Constructable::getOwner(){
	return this->owner;
}
