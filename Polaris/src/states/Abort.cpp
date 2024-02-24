// Abort state
// This state will close any control surfaces and slowly log data

#include "Abort.h"
#include "State.h"

Abort::Abort(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : State(flash, stateEstimator, xbee, servos, openMV){}

void Abort::initialize_impl() {}

void Abort::loop_impl()
{
    // shut down all systems, log slowly, retract camera 

    // busy wait
    delay(500);
}

State *Abort::nextState_impl()
{
    return nullptr;
}

enum StateId Abort::getId() {
    return StateId::ID_Abort;
}