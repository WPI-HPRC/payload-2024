#include "Recovery.h"
#include "State.h"

Recovery::Recovery(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : State(flash, attitudeStateEstimator, xbee, servos, openMV){}

void Recovery::initialize_impl() {}

void Recovery::loop_impl() {}

State *Recovery::nextState_impl() {

}

enum StateId Recovery::getId()
{
    return StateId::ID_Recovery;
}
