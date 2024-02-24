#include "State.h"
#include "Freefall.h"
#include "WindLeft.h"
#include "FlightParams.hpp"

Freefall::Freefall(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}
void Freefall::initialize_impl() {
	this->stateStartTime = this->currentTime; 
}
void Freefall::loop_impl() {
		this->stateTime = this->currentTime - this->stateStartTime; 
		if(this->stateTime > MAX_STABALIZE_TIME ){
			this->servos->cameraServo->setServo(CAM_OUT); 
			//think of best way to start flow of camera data, just do it in each state?  
		}
}
State *Freefall::nextState_impl() {
	if (this->stateTime > MAX_FREEFALL_TIME)
	{	
		Serial.println("Entering WindLeft!");
		return new WindLeft(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV);
	}
	return nullptr;
}

enum StateId Freefall::getId()
{
    return StateId::ID_Freefall;
}
