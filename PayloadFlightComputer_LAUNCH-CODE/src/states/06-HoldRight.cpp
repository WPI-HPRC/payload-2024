#include "State.h"
#include "06-HoldRight.h"
#include "07-LandPrep.h"
#include "FlightParams.hpp"


HoldRight::HoldRight(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void HoldRight::initialize_impl() {
}

void HoldRight::loop_impl() {
}

State *HoldRight::nextState_impl() {
	if (currentTime > MAX_HOLD_TIME || telemPacket.altitude < MIN_ALT)
	{	
		#ifdef TEST_STATE_MACHINE 
		Serial.println("Entering LandPrep!");
		#endif
		return new LandPrep(sensors, servos, attitudeStateEstimator);
	}
	return nullptr;
}

enum StateId HoldRight::getId()
{
    return StateId::ID_HoldRight;
}