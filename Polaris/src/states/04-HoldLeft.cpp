#include "State.h"
#include "04-HoldLeft.h"
#include "05-WindRight.h"
#include "FlightParams.hpp"


HoldLeft::HoldLeft(Sensorboard *sensors, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(sensors, attitudeStateEstimator, xbee, servos, openMV){}

void HoldLeft::initialize_impl() {
	stateStartTime = currentTime;
}

void HoldLeft::loop_impl() {
	stateTime = currentTime - stateStartTime; 
	//Do we need to continue running servos throughout all states? 
}

State *HoldLeft::nextState_impl() {
	if (stateTime > MAX_HOLD_TIME)
	{
		Serial.println("Entering WindRight!");
		return new WindRight(sensors, attitudeStateEstimator, xbee, servos, openMV);
	}
	return nullptr;
}

enum StateId HoldLeft::getId()
{
    return StateId::ID_HoldLeft;
}
