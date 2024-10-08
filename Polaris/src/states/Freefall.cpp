#include "State.h"
#include "Freefall.h"
#include "WindLeft.h"
#include "FlightParams.hpp"

Freefall::Freefall(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, attitudeStateEstimator, xbee, servos, openMV){}
void Freefall::initialize_impl() {
	this->stateStartTime = this->currentTime; 
}
void Freefall::loop_impl() {
		this->stateTime = this->currentTime - this->stateStartTime; 
		if(this->stateTime > MAX_STABALIZE_TIME ){
			this->servos->cameraServo->writeServo(CAM_OUT); 
		}
}
State *Freefall::nextState_impl() {
	if (this->stateTime > MAX_FREEFALL_TIME)
	{	
		Serial.println("Entering WindLeft!");
		return new WindLeft(this->flash, this->attitudeStateEstimator, this->xbee, this->servos, this->openMV);
	}
	return nullptr;
}

enum StateId Freefall::getId()
{
    return StateId::ID_Freefall;
}
