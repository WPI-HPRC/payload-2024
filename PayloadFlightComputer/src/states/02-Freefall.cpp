#include "State.h"
#include "Freefall.h"
#include "WindLeft.h"
#include "FlightParams.hpp"

Freefall::Freefall(struct Sensors *sensors, StateEstimator *stateEstimator) : State(sensors, stateEstimator) {}
void Freefall::initialize_impl() { 

}
void Freefall::loop_impl() {

		if(this->stateTime > MAX_STABALIZE_TIME ){
			//servos are being worked on
			this->servos->cameraServo->writeServo(CAM_OUT); 
		}
}
State *Freefall::nextState_impl() {
	if (this->stateTime > MAX_FREEFALL_TIME)
	{	
		Serial.println("Entering WindLeft!");
		return new WindLeft(sensors, stateEstimator);
	}
	return nullptr;
}

enum StateId Freefall::getId()
{
    return StateId::ID_Freefall;
}
