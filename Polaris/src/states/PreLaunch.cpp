#include "PreLaunch.h"
#include "State.h"
#include "Stowed.h"
#include "FlightParams.hpp"


PreLaunch::PreLaunch(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}

void PreLaunch::initialize_impl() {
	this->stateStartTime = this->currentTime; 
}

void PreLaunch::loop_impl() {

	this->stateTime = this->currentTime - this->stateStartTime; 
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
		return new Stowed(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV); 
	}
	return nullptr;
}

enum StateId PreLaunch::getId()
{
    return StateId::ID_PreLaunch;
}