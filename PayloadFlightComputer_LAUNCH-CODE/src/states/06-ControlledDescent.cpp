#include "State.h"
#include "06-ControlledDescent.h"
#include "07-LandPrep.h"
#include "FlightParams.hpp"


ControlledDescent::ControlledDescent(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void ControlledDescent::initialize_impl() {
}

void ControlledDescent::loop_impl() {
}

State *ControlledDescent::nextState_impl() {
	if (true)
	{
		return new LandPrep(sensors, servos, attitudeStateEstimator);
	}
	return nullptr;
}

enum StateId ControlledDescent::getId()
{
    return StateId::ID_ControlledDescent;
}