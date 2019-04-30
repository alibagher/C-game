#include "yellowPlayer.h"
#include "board.h"

YellowPlayer *YellowPlayer::instance = nullptr;

YellowPlayer::YellowPlayer(): Player{"Yellow"}{}

YellowPlayer::~YellowPlayer(){
	delete this->instance;
}