#ifndef BLUEPLAYER_H
#define BLUEPLAYER_H
#include "player.h"

class BluePlayer: public Player {
	static BluePlayer *instance;

	public:
		static BluePlayer *getInstance(){
			if (!instance){
				instance = new BluePlayer();
			}

			return instance;
		}

		~BluePlayer();

	private:
		BluePlayer();
};

#endif
