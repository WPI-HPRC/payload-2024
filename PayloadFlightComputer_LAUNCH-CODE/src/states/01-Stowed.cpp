#include "01-Stowed.h"
#include "State.h"
#include "FlightParams.hpp"
#include "02-Freefall.h"
#include "Abort.h"



Stowed::Stowed(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator){}


void Stowed::initialize_impl() {
	
}

void Stowed::loop_impl() { 
	float velocity = (telemPacket.altitude - lastAltitude) / (deltaTime / 1000.0);
    lastAltitude = telemPacket.altitude;

    // add to buffer
    velocityBuffer[bufferIndex] = velocity;
    
    // average all values in the buffer
    float sum = 0.0;
    float averageVelocity = 0.0;
    for (int i = 0; i < 10; i++)
    {
        sum += velocityBuffer[i];
    }
    averageVelocity = sum / 10.0;

    bufferIndex = (bufferIndex + 1) % 10;

  if (passedDeployHeight) {
		if(telemPacket.altitude < PAYLOAD_DEPLOY_HEIGHT){
			released = releasedDebouncer.checkOut(averageVelocity < 0);
		}
	} else {
		passedDeployHeight = passedDeployHeightDebouncer.checkOut(telemPacket.altitude > PAYLOAD_DEPLOY_HEIGHT);
	}
}

//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *Stowed::nextState_impl()
{	

	#ifdef TEST_STATE_MACHINE

    if (currentTime > MAX_PRELAUNCH) //Time is the same so just used Prelaunch param 
    {
        Serial.println("Entering Freefall!"); 
        return new Freefall(sensors, servos, attitudeStateEstimator);
    }

	#endif
	
	if(released){
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
