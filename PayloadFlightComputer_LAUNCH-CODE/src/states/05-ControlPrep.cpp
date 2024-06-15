#include "State.h"
#include "06-ControlledDescent.h"
#include "05-ControlPrep.h"
#include "FlightParams.hpp"


ControlPrep::ControlPrep(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void ControlPrep::initialize_impl() {
}

void ControlPrep::loop_impl() {
}

State *ControlPrep::nextState_impl() {
	if (true)
	{
		return new ControlledDescent(sensors, servos, attitudeStateEstimator);
	}
	return nullptr;
}

enum StateId ControlPrep::getId()
{
    return StateId::ID_ControlPrep;
}