#include "State.h"
#include "05-WindRight.h"
#include "06-HoldRight.h"
#include "FlightParams.hpp"

WindRight::WindRight(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, attitudeStateEstimator, xbee, servos, openMV){}

void WindRight::initialize_impl() {
	stateStartTime = currentTime;
}

void WindRight::loop_impl() {
	stateTime = currentTime - stateStartTime;
	
	if(stateTime < MAX_SERVO_WIND_TIME){
		servos->paraServo_3->writeServo(SERVO_COUNTER_UNWIND); 
		servos->paraServo_4->writeServo(SERVO_CLOCK_UNWIND); ; //Check Servo values 

		servos->paraServo_1->writeServo(SERVO_COUNTER_WIND); 
		servos->paraServo_2->writeServo(SERVO_CLOCK_WIND);  //Check Servo values 
	}
	else{
		servos->paraServo_3->writeServo(SERVO_CENTER); 
		servos->paraServo_4->writeServo(SERVO_CENTER);  //Check Servo values

		servos->paraServo_1->writeServo(SERVO_CENTER); 
		servos->paraServo_2->writeServo(SERVO_CENTER);  //Check Servo values
	}
}

State *WindRight::nextState_impl() {
	if (stateTime > MAX_SERVO_WIND_TIME /*||servo values = MAX_SERVO_POS*/)
	{
		//stop servos 
        #ifdef DEBUG_MODE
		Serial.println("Entering HoldRight!");
        #endif
		return new HoldRight(flash, attitudeStateEstimator, xbee, servos, openMV);
	}
	return nullptr;
}

enum StateId WindRight::getId()
{
    return StateId::ID_WindRight;
}