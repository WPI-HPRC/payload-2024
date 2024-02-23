#include "Stowed.h"
#include "State.h"
#include "Stabalize.h"
#include "FlightParams.hpp"


Stowed::Stowed(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos){} {
}

void Stowed::initialize_impl() {
}

void Stowed::loop_impl() { //Shouldn't need anything in here 
	// Read bno for example
	
	// read 10 altitude samples and take average 
		// ~ when samples average to less than 1300 feet then enter next state 
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *Stowed::nextState_impl()
{
	//this->sensorPacket.accelX or this->sensorPacket.altitude //make specific to payload 
	if (this->telemPacket.altitude < ALT_THRESHOLD_STOWED){ //Add in IR Stuff 
		Serial.println("Entering Freefall!"); 
		return new Freefall(); //make sure passing in the correct things 
	}
	return nullptr;
}

enum StateId Stowed::getId()
{
    return StateId::ID_Stowed;
}