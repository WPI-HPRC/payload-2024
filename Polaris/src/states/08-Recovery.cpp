#include "Recovery.h"
#include "State.h"

Recovery::Recovery(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : State(flash, stateEstimator, xbee, servos, openMV){}

void Recovery::initialize_impl() {}

void Recovery::loop_impl() {}

State *Recovery::nextState_impl() {
    return nullptr;
}

enum StateId Recovery::getId()
{
    return StateId::ID_Recovery;
}
