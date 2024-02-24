#include "Stowed.h"
#include "State.h"
#include "FlightParams.hpp"



Stowed::Stowed(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}


void Stowed::initialize_impl() {
	this->stateStartTime = this->currentTime; 
}

void Stowed::loop_impl() { //Shouldn't need anything in here 
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *Stowed::nextState_impl()
{
	this->stateTime = this->currentTime - this->stateStartTime; 
	if (digitalRead(IR_PIN)==HIGH || stateTime > MAX_STOW_TIME){ 
		Serial.println("Entering Freefall!"); 
		return new Freefall(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV); 
	}
	return nullptr;
}

enum StateId Stowed::getId()
{
    return StateId::ID_Stowed;
}