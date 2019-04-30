#ifndef REDPLAYER_H
#define REDPLAYER_H
#include "player.h"

class RedPlayer: public Player {
	static RedPlayer *instance;

	public:
		static RedPlayer *getInstance(){
			if (!instance){
				instance = new RedPlayer();
			}

			return instance;
		}

		~RedPlayer();
		
	private:
		RedPlayer();
};

#endif
