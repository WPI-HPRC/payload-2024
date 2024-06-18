#include "01-Stowed.h"
#include "State.h"
#include "FlightParams.hpp"



Stowed::Stowed(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator){}


void Stowed::initialize_impl() {
	
}

void Stowed::loop_impl() { //Shouldn't need anything in here 
	
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *Stowed::nextState_impl()
{	

	#ifdef TEST_STATE_MACHINE

    if (currentTime > MAX_PRELAUNCH) //Stay in Pre-Launch for 5 seconds 
    {
        Serial.println("Entering Freefall!"); 
        return new Stowed(sensors, servos, attitudeStateEstimator);
    }

	#endif
	
	if(change in acceleration > 0){
		return new Freefall(sensors, servos, attitudeStateEstimator); 
	}
	else if (currentTime > MAX_STOW_TIME){ 
		return new Abort(sensors, servos, attitudeStateEstimator); 
	}
	return nullptr;
}

enum StateId Stowed::getId()
{
    return StateId::ID_Stowed;
}