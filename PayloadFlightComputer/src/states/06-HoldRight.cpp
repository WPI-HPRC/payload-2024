#include "State.h"
#include "HoldRight.h"
#include "LandPrep.h"
#include "FlightParams.hpp"


HoldRight::HoldRight(struct Sensors *sensors, StateEstimator *stateEstimator) : State(sensors, stateEstimator) {}

void HoldRight::initialize_impl() {


}

void HoldRight::loop_impl() {

	//Again, continue running servos? 
}

State *HoldRight::nextState_impl() {
	if (this->stateTime > MAX_HOLD_TIME)
	{	
		//unwind servos
		Serial.println("Entering LandPrep!");
		return new LandPrep(sensors, stateEstimator);
	}
	return nullptr;
}

enum StateId HoldRight::getId()
{
    return StateId::ID_HoldRight;
}