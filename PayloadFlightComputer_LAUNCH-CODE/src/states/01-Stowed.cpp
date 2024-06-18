#include "01-Stowed.h"
#include "State.h"
#include "FlightParams.hpp"
#include "02-Freefall.h"
#include "Abort.h"



Stowed::Stowed(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator){}


void Stowed::initialize_impl() {
	
}

void Stowed::loop_impl() { 
	float jerk = (telemPacket.accelZ - lastAcceleration) / (deltaTime / 1000.0);
    lastAcceleration = telemPacket.accelZ;

    // add to buffer
    jerkBuffer[bufferIndex] = jerk;
    
    // average all values in the buffer
    float sum = 0.0;
    float averageJerk = 0.0;
    for (int i = 0; i < 10; i++)
    {
        sum += jerkBuffer[i];
    }
    averageJerk = sum / 10.0;

    bufferIndex = (bufferIndex + 1) % 10;

    released = releasedDebouncer.checkOut(abs(averageJerk) < JERK);

	//TO DO: FIX THIS, calculate release time 
	
	if(released && releasedTime > 1000){
		released == false; 
		releasedTime = 0; 
	}
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *Stowed::nextState_impl()
{	

	#ifdef TEST_STATE_MACHINE

    if (currentTime > MAX_PRELAUNCH) //Time is the same so just used Prelaunch param 
    {
        Serial.println("Entering Freefall!"); 
        return new Stowed(sensors, servos, attitudeStateEstimator);
    }

	#endif
	
	if(released && telemPacket.altitude < 1200){ //check alt- needs to be in meters 
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