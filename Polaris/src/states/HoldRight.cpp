#include "State.h"
#include "HoldRight.h"
#include "LandPrep.h"
#include "FlightParams.hpp"


HoldRight::HoldRight(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos), openMV(openMV){}

void HoldRight::initialize_impl() {
	this->stateStartTime = this->currentTime;

}

void HoldRight::loop_impl() {
	this->stateTime = this->currentTime - this->stateStartTime;
	//Again, continue running servos? 
}

State *HoldRight::nextState_impl() {
	if (this->stateTime > MAX_HOLD_TIME)
	{	
		//unwind servos
		Serial.println("Entering LandPrep!")
		return new LandPrep(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV);
	}
	return nullptr;
}

enum StateId HoldRight::getId()
{
    return StateId::ID_HoldRight;
}