#include "Land.h"
#include "State.h"
#include "Recovery.h"

Land::Land() {}

void Land::initialize_impl() {}

void Land::loop_impl() {
	// read 10 velocity samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}

State *Land::nextState_impl() {
	if (/*this->sensorPacket.velocity == 0 ||*/ this->currentTime > MAX_LAND_TIME)
	{
		return new Recovery();
	}
	return nullptr;
}
