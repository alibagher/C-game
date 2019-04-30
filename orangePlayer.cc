#include "orangePlayer.h"
#include "board.h"

OrangePlayer *OrangePlayer::instance = nullptr;

OrangePlayer::OrangePlayer(): Player{"Orange"}{}

OrangePlayer::~OrangePlayer(){
	delete this->instance;
}