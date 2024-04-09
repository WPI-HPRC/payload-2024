#include "State.h"
#include "HoldLeft.h"
#include "WindRight.h"
#include "FlightParams.hpp"


HoldLeft::HoldLeft(struct Sensors *sensors, StateEstimator *stateEstimator) : State(sensors, stateEstimator) {}

void HoldLeft::initialize_impl() {

}

void HoldLeft::loop_impl() {

	//Do we need to continue running servos throughout all states? 
}

State *HoldLeft::nextState_impl() {
	if (this->stateTime > MAX_HOLD_TIME)
	{
		Serial.println("Entering WindRight!");
		return new WindRight(sensors, stateEstimator);
	}
	return nullptr;
}

enum StateId HoldLeft::getId()
{
    return StateId::ID_HoldLeft;
}
