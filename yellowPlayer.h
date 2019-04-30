#ifndef YELLOWPLAYER_H
#define YELLOWPLAYER_H
#include "player.h"

class Board;

class YellowPlayer: public Player {
	static YellowPlayer *instance;

	public:
		static YellowPlayer *getInstance(){
			if (!instance){
				instance = new YellowPlayer();
			}

			return instance;
		}

		~YellowPlayer();

	private:
		YellowPlayer();
};

#endif
