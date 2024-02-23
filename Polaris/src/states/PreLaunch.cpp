#include "PreLaunch.h"
#include "State.h"
#include "Stowed.h"
#include "Debug.h"
#include "Sensors.h" //Check this 
#include "FlightParams.hpp"

#define IN_FOISE false //Need to edit to be Payload Specific, stole from PolarisLTS :)

PreLaunch::PreLaunch(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : flash(flash), stateEstimator(stateEstimator), xbee(xbee), servos(servos), openMV(openMV){}

void PreLaunch::initialize_impl() {
	this->stateStartTime = this->currentTime; 
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *PreLaunch::nextState_impl()
{
	if (this->telemPacket.accelZ > LAUNCH_ACCEL_THRESHOLD ) //Do we want to buffer/average this? 
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