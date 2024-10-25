#include "State.h"
#include "06-HoldRight.h"
#include "LandPrep.h"
#include "FlightParams.hpp"


HoldRight::HoldRight(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, attitudeStateEstimator, xbee, servos, openMV){}

void HoldRight::initialize_impl() {
	stateStartTime = currentTime;

}

void HoldRight::loop_impl() {
	stateTime = currentTime - stateStartTime;
	//Again, continue running servos? 
}

State *HoldRight::nextState_impl() {
	if (stateTime > MAX_HOLD_TIME || telemPacket.altitude < MIN_ALT) //Ported from IREC-Dev
	{	
		//unwind servos
        // Looks like nothing was implemented later :(, still WIP in my mind
        #ifdef DEBUG_MODE
		Serial.println("Entering LandPrep!");
        #endif
		return new LandPrep(flash, attitudeStateEstimator, xbee, servos, openMV);
	}
	return nullptr;
}

enum StateId HoldRight::getId()
{
    return StateId::ID_HoldRight;
}