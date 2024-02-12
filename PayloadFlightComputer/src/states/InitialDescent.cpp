#include "InitialDescent.h"
#include "State.h"
#include "ControlledDescent.h"

InitialDescent::InitialDescent(struct Sensors *sensors) : State(sensors) {

}

void InitialDescent::initialize_impl() {

}

void InitialDescent::loop_impl() {

}

State *InitialDescent::nextState_impl() {
	if (/* check IPP */this->currentTime > MAX_INITIALDESCENT_TIME)
	{
		return new ControlledDescent(sensors);
	}
	return nullptr;
}
