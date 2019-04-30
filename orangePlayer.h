#ifndef ORANGEPLAYER_H
#define ORANGEPLAYER_H
#include "player.h"

class OrangePlayer: public Player {
	static OrangePlayer *instance;

	public:
		static OrangePlayer *getInstance(){
			if (!instance){
				instance = new OrangePlayer();
			}

			return instance;
		}

		~OrangePlayer();

	private:
		OrangePlayer();
};

#endif
