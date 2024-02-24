#include "State.h"
#include "HoldLeft.h"
#include "WindRight.h"
#include "FlightParams.hpp"


HoldLeft::HoldLeft(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}

void HoldLeft::initialize_impl() {
	this->stateStartTime = this->currentTime;
}

void HoldLeft::loop_impl() {
	this->stateTime = this->currentTime - this->stateStartTime; 
	//Do we need to continue running servos throughout all states? 
}

State *HoldLeft::nextState_impl() {
	if (this->stateTime > MAX_HOLD_TIME)
	{
		Serial.println("Entering WindRight!");
		return new WindRight(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV);
	}
	return nullptr;
}

enum StateId HoldLeft::getId()
{
    return StateId::ID_HoldLeft;
}
