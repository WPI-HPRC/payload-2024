#include "State.h"
#include "Freefall.h"
#include "WindLeft.h"

Freefall::Freefall() {}
void Freefall::initialize_impl() {

}
void Freefall::loop_impl() {
// read 10 accelZ samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}
State *Freefall::nextState_impl() {
	if (/*this->sensorPacket.accelZ >*/ ACC_THRESHOLD_STABALIZE || this->currentTime > MAX_STABALIZE_TIME)
	{
		return new WindLeft();
	}
	return nullptr;
}

enum StateId Freefall::getId()
{
    return StateId::ID_Freefall;
}
