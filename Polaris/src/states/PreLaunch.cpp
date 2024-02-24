#include "PreLaunch.h"
#include "State.h"
#include "Stowed.h"
#include "FlightParams.hpp"


#define IN_FOISE false //Need to edit to be Payload Specific, stole from PolarisLTS :)

PreLaunch::PreLaunch(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}

void PreLaunch::initialize_impl() {
	this->stateStartTime = this->currentTime; 
}

void PreLaunch::loop_impl() {
	this->stateTime = this->currentTime - this->stateStartTime; 
	Serial.println("I am in Pre-Launch"); 
}


//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *PreLaunch::nextState_impl()
{
	if (this->stateTime > 5000) //Do we want to buffer/average this? 
	{
		Serial.println("Entering Stowed!"); 
		return new Stowed(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV); 
	}
	return nullptr;
}

enum StateId PreLaunch::getId()
{
    return StateId::ID_PreLaunch;
}