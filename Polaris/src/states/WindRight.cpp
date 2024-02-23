#include "WindRight.h"
#include "State.h"
#include "HoldRight.h"
#include "FlightParams.hpp"

WindRight::WindRight(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos), openMV(openMV){}
	

void WindRight::initialize_impl() {
	this->stateStartTime = this->currentTime;
}

void WindRight::loop_impl() {
	this->stateTime = this->currentTime - this->stateStartTime;
	this->servos->paraServo_1.adjustString(STRING_BASE_LENGTH); 
	this->servos->paraServo_3.adjustString(STRING_BASE_LENGTH); 
	this->servos->paraServo_2.adjustString(DESIRED_STRING_LENGTH); 
	this->servos->paraServo_4.adjustString(DESIRED_STRING_LENGTH); //Check Servo values  
}

State *WindRight::nextState_impl() {
	if (this->stateTime > MAX_SERVO_WIND_TIME /*||servo values = MAX_SERVO_POS*/)
	{
		//stop servos 
		Serial.println("Entering HoldRight!")
		return new HoldRight(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV);
	}
	return nullptr;
}

enum StateId WindRight::getId()
{
    return StateId::ID_WindRight;
}