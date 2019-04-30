#include "redPlayer.h"
#include "board.h"

RedPlayer *RedPlayer::instance = nullptr;

RedPlayer::RedPlayer(): Player{"Red"}{}

RedPlayer::~RedPlayer(){
	delete this->instance;
}