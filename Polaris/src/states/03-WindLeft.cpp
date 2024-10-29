#include "03-WindLeft.h"
#include "State.h"
#include "04-HoldLeft.h"
#include "FlightParams.hpp"

WindLeft::WindLeft(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, attitudeStateEstimator, xbee, servos, openMV){}

void WindLeft::initialize_impl() {
	stateStartTime = currentTime;
}

void WindLeft::loop_impl() {
	stateTime = currentTime - stateStartTime; 
	if(stateTime < MAX_SERVO_WIND_TIME){
		servos->paraServo_3->writeServo(SERVO_COUNTER_WIND); 
		servos->paraServo_4->writeServo(SERVO_CLOCK_WIND); ; //Check Servo values 
	}
	else{
		servos->paraServo_3->writeServo(SERVO_CENTER); 
		servos->paraServo_4->writeServo(SERVO_CENTER); ; //Check Servo values
	}
	
}

State *WindLeft::nextState_impl() {
	if (stateTime > MAX_SERVO_WIND_TIME /*||servo values = MAX_SERVO_POS*/)
	{
		//stop servos 
        #ifdef DEBUG_MODE
		Serial.println("Entering HoldLeft!"); 
        #endif
		return new HoldLeft(flash,attitudeStateEstimator,xbee,servos,openMV);
	}
	return nullptr;
}

enum StateId WindLeft::getId()
{
    return StateId::ID_WindLeft;
}
