#include "LandPrep.h"
#include "State.h"
#include "Recovery.h"
#include "FlightParams.hpp"

LandPrep::LandPrep(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : State(flash, stateEstimator, xbee, servos, openMV){}

void LandPrep::initialize_impl() {}

void LandPrep::loop_impl() {
	this->servos->paraServo_2->adjustString(STRING_BASE_LENGTH); 
	this->servos->paraServo_4->adjustString(STRING_BASE_LENGTH); 
	this->servos->cameraServo->setServo(CAM_RETRACT); 
}

State *LandPrep::nextState_impl() {
	if (0) //FIX TO BE VELOCITIES 
	{	
		Serial.println("Entering Recovery!");
		return new Recovery(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV);
	}
	return nullptr;
}

enum StateId LandPrep::getId()
{
    return StateId::ID_LandPrep;
}
