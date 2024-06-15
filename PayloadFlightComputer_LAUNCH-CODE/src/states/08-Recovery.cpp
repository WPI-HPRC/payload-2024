#include "08-Recovery.h"
#include "State.h"

Recovery::Recovery(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void Recovery::initialize_impl() {}

void Recovery::loop_impl() {}

State *Recovery::nextState_impl() {
    return nullptr; 

}

enum StateId Recovery::getId()
{
    return StateId::ID_Recovery;
}
