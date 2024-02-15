#include "State.h"
#include "HoldLeft.h"
#include "WindRight.h"


HoldLeft::HoldLeft() {

}

void HoldLeft::initialize_impl() {

}

void HoldLeft::loop_impl() {
// read 10 altitude samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}

State *HoldLeft::nextState_impl() {
	if (/*this->sensorPacket.altitude <*/ ALT_THRESHOLD_CONTROLLED ||this->currentTime > MAX_CONTROLLED_DESCENT_TIME)
	{
		return new WindRight();
	}
	return nullptr;
}

enum StateId HoldLeft::getId()
{
    return StateId::ID_HoldLeft;
}
