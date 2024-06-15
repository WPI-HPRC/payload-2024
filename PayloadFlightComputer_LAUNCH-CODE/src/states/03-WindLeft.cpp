#include "03-WindLeft.h"
#include "State.h"
#include "04-HoldLeft.h"
#include "FlightParams.hpp"

WindLeft::WindLeft(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void WindLeft::initialize_impl() {
	
}

void WindLeft::loop_impl() {

	if(currentTime < 1500){
		servos->paraServo_3->writeServo(SERVO_COUNTER_WIND); 
		servos->paraServo_4->writeServo(SERVO_CLOCK_WIND); //Check Servo values 
	}
	else{
		servos->paraServo_3->writeServo(SERVO_CENTER); 
		servos->paraServo_4->writeServo(SERVO_CENTER); //Check Servo values
	}
	
}

State *WindLeft::nextState_impl() {
	if (currentTime > MAX_SERVO_WIND_TIME /*||servo values = MAX_SERVO_POS*/)
	{
		//stop servos 
		Serial.println("Entering HoldLeft!"); 
		return new HoldLeft(sensors, servos, attitudeStateEstimator);
	}
	return nullptr;
}

enum StateId WindLeft::getId()
{
    return StateId::ID_WindLeft;
}