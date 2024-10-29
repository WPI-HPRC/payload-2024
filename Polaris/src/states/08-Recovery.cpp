#include "08-Recovery.h"
#include "State.h"

Recovery::Recovery(Sensorboard *sensors, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : State(sensors, attitudeStateEstimator, xbee, servos, openMV){}

void Recovery::initialize_impl() {}

void Recovery::loop_impl() {}

State *Recovery::nextState_impl() {
    return nullptr;
}

enum StateId Recovery::getId()
{
    return StateId::ID_Recovery;
}
