#include "State.h"
#include "02-Freefall.h"
#include "03-WindLeft.h"
#include "FlightParams.hpp"

Freefall::Freefall(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void Freefall::initialize_impl() {}

void Freefall::loop_impl() {
		
	if(currentTime > MAX_STABALIZE_TIME ){
		servos->cameraServo->writeServo(CAM_OUT); 
	}
}

State *Freefall::nextState_impl() {
	if (currentTime > MAX_FREEFALL_TIME)
	{	
		#ifdef TEST_STATE_MACHINE 
		Serial.println("Entering WindLeft!");
		#endif
		return new WindLeft(sensors, servos, attitudeStateEstimator);
	}
	return nullptr;
}

enum StateId Freefall::getId()
{
    return StateId::ID_Freefall;
}
