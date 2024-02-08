#include "State.h"
#include "ControlledDescent.h"
#include "Land.h"


ControlledDescent::ControlledDescent() {

}

void ControlledDescent::initialize_impl() {

}

void ControlledDescent::loop_impl() {
// read 10 altitude samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}

State *ControlledDescent::nextState_impl() {
	if (/*this->sensorPacket.altitude <*/ ALT_THRESHOLD_CONTROLLED ||this->currentTime > MAX_CONTROLLED_DESCENT_TIME)
	{
		return new Land();
	}
	return nullptr;
}
