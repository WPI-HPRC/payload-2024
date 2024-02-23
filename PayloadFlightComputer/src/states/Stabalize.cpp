#include "State.h"
#include "Stabalize.h"
#include "InitialDescent.h"

Stabalize::Stabalize() {}
void Stabalize::initialize_impl() {

}
void Stabalize::loop_impl() {
// read 10 accelZ samples and take average 
		// ~ when samples average to greater than threshold then enter next state 
}
State *Stabalize::nextState_impl() {
	if (/*this->sensorPacket.accelZ >*/ ACC_THRESHOLD_STABALIZE || this->currentTime > MAX_STABALIZE_TIME)
	{
		return new InitialDescent();
	}
	return nullptr;
}
