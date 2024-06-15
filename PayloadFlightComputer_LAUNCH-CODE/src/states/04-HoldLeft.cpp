#include "State.h"
#include "04-HoldLeft.h"
#include "05-ControlPrep.h"
#include "FlightParams.hpp"


HoldLeft::HoldLeft(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void HoldLeft::initialize_impl() {
}

void HoldLeft::loop_impl() {
}

State *HoldLeft::nextState_impl() {
	if (currentTime > MAX_HOLD_TIME)
	{
		return new ControlPrep(sensors, servos, attitudeStateEstimator);
	}
	return nullptr;
}

enum StateId HoldLeft::getId()
{
    return StateId::ID_HoldLeft;
}