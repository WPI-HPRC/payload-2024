#include "WindLeft.h"
#include "State.h"
#include "HoldLeft.h"
#include "FlightParams.hpp"

WindLeft::WindLeft(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos){}

void WindLeft::initialize_impl() {}

void WindLeft::loop_impl() {
	//wind left servos 
}

State *WindLeft::nextState_impl() {
	if (this->currentTime > MAX_SERVO_WIND_TIME /*||servo values = MAX_SERVO_POS*/)
	{
		//stop servos 
		Serial.println("Entering HoldLeft!")
		return new HoldLeft();
	}
	return nullptr;
}

enum StateId WindLeft::getId()
{
    return StateId::ID_WindLeft;
}
