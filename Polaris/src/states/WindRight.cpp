#include "WindRight.h"
#include "State.h"
#include "HoldRight.h"

WindLeft::WindRight() {
	
}

void WindRight::initialize_impl() {

}

void WindRight::loop_impl() {

}

State *WindRight::nextState_impl() {
	if (/* check IPP */this->currentTime > MAX_INITIALDESCENT_TIME)
	{
		return new HoldRight();
	}
	return nullptr;
}

enum StateId WindRight::getId()
{
    return StateId::ID_WindRight;
}