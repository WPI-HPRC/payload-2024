#include "LandPrep.h"
#include "State.h"
#include "Recovery.h"

LandPrep::LandPrep() {}

void LandPrep::initialize_impl() {}

void LandPrep::loop_impl() {
	// read 10 velocity samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}

State *LandPrep::nextState_impl() {
	if (/*this->sensorPacket.velocity == 0 ||*/ this->currentTime > MAX_LAND_TIME)
	{
		return new Recovery();
	}
	return nullptr;
}

enum StateId LandPrep::getId()
{
    return StateId::ID_LandPrep;
}
