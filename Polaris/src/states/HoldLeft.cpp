#include "State.h"
#include "HoldLeft.h"
#include "WindRight.h"
#include "FlightParams.hpp"


HoldLeft::HoldLeft() {}

void HoldLeft::initialize_impl() {}

void HoldLeft::loop_impl() {
// read 10 altitude samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}

State *HoldLeft::nextState_impl() {
	if (this->currentTime > MAX_HOLD_TIME)
	{
		Serial.println("Entering WindRight!")
		return new WindRight();
	}
	return nullptr;
}

enum StateId HoldLeft::getId()
{
    return StateId::ID_HoldLeft;
}
