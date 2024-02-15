#include "State.h"
#include "HoldRight.h"
#include "LandPrep.h"


HoldRight::HoldRigh() {

}

void HoldRigh::initialize_impl() {

}

void HoldRigh::loop_impl() {
// read 10 altitude samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}

State *HoldRigh::nextState_impl() {
	if (/*this->sensorPacket.altitude <*/ ALT_THRESHOLD_CONTROLLED ||this->currentTime > MAX_CONTROLLED_DESCENT_TIME)
	{
		return new LandPrep();
	}
	return nullptr;
}

enum StateId HoldRight::getId()
{
    return StateId::ID_HoldRight;
}