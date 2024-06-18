#include "06-Abort.h"
#include "State.h"

Abort::Abort(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void Abort::initialize_impl() {}

void Abort::loop_impl()
{}

State *Abort::nextState_impl()
{
    return nullptr;
}

enum StateId Abort::getId() {
    return StateId::ID_Abort;
}