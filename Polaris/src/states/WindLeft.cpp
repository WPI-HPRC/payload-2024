#include "WindLeft.h"
#include "State.h"
#include "HoldLeft.h"
#include "FlightParams.hpp"

WindLeft::WindLeft(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}

void WindLeft::initialize_impl() {
	this->stateStartTime = this->currentTime;
}

void WindLeft::loop_impl() {
	this->stateTime = this->currentTime - this->stateStartTime; 
	if(stateTime < 1500){
		this->servos->paraServo_3->writeServo(SERVO_COUNTER_WIND); 
		this->servos->paraServo_4->writeServo(SERVO_CLOCK_WIND); ; //Check Servo values 
	}
	else{
		this->servos->paraServo_3->writeServo(SERVO_CENTER); 
		this->servos->paraServo_4->writeServo(SERVO_CENTER); ; //Check Servo values
	}
	
}

State *WindLeft::nextState_impl() {
	if (this->stateTime > MAX_SERVO_WIND_TIME /*||servo values = MAX_SERVO_POS*/)
	{
		//stop servos 
		Serial.println("Entering HoldLeft!"); 
		return new HoldLeft(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV);
	}
	return nullptr;
}

enum StateId WindLeft::getId()
{
    return StateId::ID_WindLeft;
}
