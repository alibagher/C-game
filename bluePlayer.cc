#include "bluePlayer.h"

BluePlayer *BluePlayer::instance = nullptr;

BluePlayer::BluePlayer(): Player{"Blue"}{}

BluePlayer::~BluePlayer(){
	delete this->instance;
}