#include "WindRight.h"
#include "State.h"
#include "HoldRight.h"
#include "FlightParams.hpp"

WindRight::WindRight(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos){}
	

void WindRight::initialize_impl() {

}

void WindRight::loop_impl() {
	//unwind left servos
	//wind right servos 
}

State *WindRight::nextState_impl() {
	if (this->currentTime > MAX_SERVO_WIND_TIME /*||servo values = MAX_SERVO_POS*/)
	{
		//stop servos 
		Serial.println("Entering HoldRight!")
		return new HoldRight();
	}
	return nullptr;
}

enum StateId WindRight::getId()
{
    return StateId::ID_WindRight;
}