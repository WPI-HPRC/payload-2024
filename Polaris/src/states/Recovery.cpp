#include "Recovery.h"
#include "State.h"

Recovery::Recovery(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos), openMV(openMV){}

void Recovery::initialize_impl() {}

void Recovery::loop_impl() {}

State *Recovery::nextState_impl() {

}

enum StateId Recovery::getId()
{
    return StateId::ID_Recovery;
}
