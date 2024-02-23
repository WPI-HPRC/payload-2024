#include "State.h"
#include "HoldRight.h"
#include "LandPrep.h"
#include "FlightParams.hpp"


HoldRight::HoldRight(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos){}

void HoldRight::initialize_impl() {

}

void HoldRight::loop_impl() {
// read 10 altitude samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}

State *HoldRight::nextState_impl() {
	if (this->currentTime > MAX_HOLD_TIME)
	{	
		//unwind servos
		Serial.println("Entering LandPrep!")
		return new LandPrep();
	}
	return nullptr;
}

enum StateId HoldRight::getId()
{
    return StateId::ID_HoldRight;
}