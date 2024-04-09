#include "Recovery.h"
#include "State.h"

Recovery::Recovery(struct Sensors *sensors, StateEstimator *stateEstimator) : State(sensors, stateEstimator) {}

void Recovery::initialize_impl() {}

void Recovery::loop_impl() {}

State *Recovery::nextState_impl() {

}

enum StateId Recovery::getId()
{
    return StateId::ID_Recovery;
}
