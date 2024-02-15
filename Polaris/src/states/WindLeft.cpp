#include "WindLeft.h"
#include "State.h"
#include "ControlledDescent.h"

WindLeft::WindLeft() {
	
}

void WindLeft::initialize_impl() {

}

void WindLeft::loop_impl() {

}

State *WindLeft::nextState_impl() {
	if (/* check IPP */this->currentTime > MAX_INITIALDESCENT_TIME)
	{
		return new HoldLeft();
	}
	return nullptr;
}

enum StateId WindLeft::getId()
{
    return StateId::ID_WindLeft;
}
