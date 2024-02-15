#include "Stowed.h"
#include "State.h"
#include "Stabalize.h"


Stowed::Stowed() {
}

void Stowed::initialize_impl() {
}

void Stowed::loop_impl() {
	// Read bno for example
	
	// read 10 altitude samples and take average 
		// ~ when samples average to less than 1300 feet then enter next state 
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *Stowed::nextState_impl()
{
	//this->sensorPacket.accelX or this->sensorPacket.altitude //make specific to payload 
	if (/*this->sensorPacket.altitude <*/ ALT_THRESHOLD_STOWED || this->currentTime > MAX_STOWED_TIME ){
		return new Stabalize();
	}
	return nullptr;
}

enum StateId Stowed::getId()
{
    return StateId::ID_Stowed;
}