#include "State.h"
#include "04-HoldLeft.h"
#include "05-WindRight.h"
#include "FlightParams.hpp"


HoldLeft::HoldLeft(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void HoldLeft::initialize_impl() {
}

void HoldLeft::loop_impl() {
}

State *HoldLeft::nextState_impl() {
	if (currentTime > MAX_HOLD_TIME)
	{
        #ifdef TEST_STATE_MACHINE 
		Serial.println("Entering WindRight!");
		#endif
		return new WindRight(sensors, servos, attitudeStateEstimator);
	}
	return nullptr;
}

enum StateId HoldLeft::getId()
{
    return StateId::ID_HoldLeft;
}