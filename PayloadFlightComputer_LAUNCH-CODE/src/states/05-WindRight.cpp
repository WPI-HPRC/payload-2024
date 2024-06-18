#include "State.h"
#include "06-HoldRight.h"
#include "05-WindRight.h"
#include "FlightParams.hpp"


WindRight::WindRight(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void WindRight::initialize_impl() {
}

void WindRight::loop_impl() {
	if(currentTime < MAX_SERVO_WIND_TIME){
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
	if (currentTime > MAX_SERVO_WIND_TIME)
	{
		#ifdef TEST_STATE MACHINE 
		Serial.println("Entering HoldRight!");
		#endif
		return new HoldRight(sensors, servos, attitudeStateEstimator);
	}
	return nullptr;
}

enum StateId WindRight::getId()
{
    return StateId::ID_WindRight;
}