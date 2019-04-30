#ifndef CONSTRUCTABLE_H
#define CONSTRUCTABLE_H
#include <iostream>
#include "subject.h"
#include "observer.h"

class Player;

class Constructable: public Subject, public Observer {
	Player *owner;
	std::vector<Player*> playersThatCanBuild;
	bool buildable;

	public:
		Constructable();

		void clear();
		Player *getOwner();

		bool build(Player *player, bool init = false);

		virtual void printSaveFormat(std::ostream &out) = 0;
		virtual void doBuild() = 0;

	protected:
		bool canPlayerBuild(Player *player);
		void setPlayerCanBuild(Player *player);
		void setUnBuildable();
};

#endif