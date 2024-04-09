#include "PreLaunch.h"
#include "State.h"
#include "Stowed.h"
#include "FlightParams.hpp"


PreLaunch::PreLaunch(struct Sensors *sensors, StateEstimator *stateEstimator) : State(sensors, stateEstimator) {}

void PreLaunch::initialize_impl() { 
}

void PreLaunch::loop_impl() {
	//Serial.println("I am in Pre-Launch");
	Serial.println(telemPacket.accelZ); 
	verticalAcceleration = telemPacket.accelZ; 
	verticalAccelerationBuffer[bufferIndex] = verticalAcceleration;
    
    // average all values in the buffer
    float sum = 0.0;
    float averageVerticalAcceleration = 0.0;
    for (int i = 0; i < 10; i++)
    {
        sum += verticalAccelerationBuffer[i];
    }
	

    averageVerticalAcceleration = sum / 10.0;
	//Serial.println(averageVerticalAcceleration); 

	if(averageVerticalAcceleration < LAUNCH_ACCEL_THRESHOLD){
		count++; 
	}
	else{
		count = 0; 
	}

	if(count > 2){ //change
		launched = true; 
	}

    bufferIndex = (bufferIndex + 1) % 10;
}


//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *PreLaunch::nextState_impl()
{
	if (launched) 
	{
		Serial.println("Entering Stowed!"); 
		return new Stowed(sensors, stateEstimator); 
	}
	return nullptr;
}

enum StateId PreLaunch::getId()
{
    return StateId::ID_PreLaunch;
}