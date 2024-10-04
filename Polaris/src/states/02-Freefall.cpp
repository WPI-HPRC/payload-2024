#include "State.h"
#include "02-Freefall.h"
#include "WindLeft.h"
#include "FlightParams.hpp"

Freefall::Freefall(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}
void Freefall::initialize_impl() {
	stateStartTime = currentTime; 
}
void Freefall::loop_impl() {
		stateTime = currentTime - stateStartTime; 
		if(stateTime > MAX_STABILIZE_TIME ){
            #ifdef DEBUG_MODE
            Serial.println("Camera Deployed!");
            #endif
			servos->cameraServo->writeServo(CAM_OUT); 
		}
}
State *Freefall::nextState_impl() {
	if (stateTime > MAX_FREEFALL_TIME)
	{	
        #ifdef DEBUG_MODE
		Serial.println("Entering WindLeft!");
        #endif
		return new WindLeft(flash, stateEstimator, xbee, servos, openMV);
	}
	return nullptr;
}

enum StateId Freefall::getId()
{
    return StateId::ID_Freefall;
}
