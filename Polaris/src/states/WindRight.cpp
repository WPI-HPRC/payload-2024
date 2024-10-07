#include "WindRight.h"
#include "State.h"
#include "HoldRight.h"
#include "FlightParams.hpp"

WindRight::WindRight(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}
	

void WindRight::initialize_impl() {
	this->stateStartTime = this->currentTime;
}

void WindRight::loop_impl() {
	this->stateTime = this->currentTime - this->stateStartTime;
	
	if(stateTime < 1500){
		this->servos->paraServo_3->writeServo(SERVO_COUNTER_UNWIND); 
		this->servos->paraServo_4->writeServo(SERVO_CLOCK_UNWIND); ; //Check Servo values 

		this->servos->paraServo_1->writeServo(SERVO_COUNTER_WIND); 
		this->servos->paraServo_2->writeServo(SERVO_CLOCK_WIND);  //Check Servo values 
	}
	else{
		this->servos->paraServo_3->writeServo(SERVO_CENTER); 
		this->servos->paraServo_4->writeServo(SERVO_CENTER);  //Check Servo values

		this->servos->paraServo_1->writeServo(SERVO_CENTER); 
		this->servos->paraServo_2->writeServo(SERVO_CENTER);  //Check Servo values
	}
}

State *WindRight::nextState_impl() {
	if (this->stateTime > MAX_SERVO_WIND_TIME /*||servo values = MAX_SERVO_POS*/)
	{
		//stop servos 
		Serial.println("Entering HoldRight!"); 
		return new HoldRight(this->flash, this->attitudeStateEstimator, this->xbee, this->servos, this->openMV);
	}
	return nullptr;
}

enum StateId WindRight::getId()
{
    return StateId::ID_WindRight;
}