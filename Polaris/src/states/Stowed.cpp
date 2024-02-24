#include "Stowed.h"
#include "State.h"
#include "Stabalize.h"
#include "FlightParams.hpp"


Stowed::Stowed(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, Utility::Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}


void Stowed::initialize_impl() {
	this->stateStartTime = this->currentTime; 
}

void Stowed::loop_impl() { //Shouldn't need anything in here 
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *Stowed::nextState_impl()
{
	//this->sensorPacket.accelX or this->sensorPacket.altitude //make specific to payload 
	if (this->telemPacket.altitude < ALT_THRESHOLD_STOWED){ //Add in IR Stuff 
		Serial.println("Entering Freefall!"); 
		return new Freefall(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV); //make sure passing in the correct things 
	}
	return nullptr;
}

enum StateId Stowed::getId()
{
    return StateId::ID_Stowed;
}