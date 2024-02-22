#include "LandPrep.h"
#include "State.h"
#include "Recovery.h"
#include "FlightParams.hpp"

LandPrep::LandPrep(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos){}

void LandPrep::initialize_impl() {}

void LandPrep::loop_impl() {
	// read 10 velocity samples and take average, integrate acceleration 
		// ~ when samples average to greater than threshold then enter next state 
	//fold in camera servo 
}

State *LandPrep::nextState_impl() {
	if (/*Velocity readings are < LANDING_VELOCITY*/ )
	{	
		Serial.println("Entering Recovery!")
		return new Recovery();
	}
	return nullptr;
}

enum StateId LandPrep::getId()
{
    return StateId::ID_LandPrep;
}
