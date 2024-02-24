#include "LandPrep.h"
#include "State.h"
#include "Recovery.h"
#include "FlightParams.hpp"

LandPrep::LandPrep(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) : State(flash, stateEstimator, xbee, servos, openMV){}

void LandPrep::initialize_impl() {}

void LandPrep::loop_impl() {
	this->servos->paraServo_2->adjustString(STRING_BASE_LENGTH);  //make sure these are correct 
	this->servos->paraServo_4->adjustString(STRING_BASE_LENGTH); 
	this->servos->cameraServo->setServo(CAM_RETRACT); 

	// calculate vertical velocity
    float verticalVelocity = (Utility::pressureToAltitude(sensorData.Pressure) - lastAltitude) / (deltaTime / 1000.0);
    lastAltitude = Utility::pressureToAltitude(sensorData.Pressure); 

    // add vertical velocity to cyclic buffer
    verticalVelocityBuffer[bufferIndex] = verticalVelocity;
    
    // average all values in the buffer
    float sum = 0.0;
    float averageVerticalVelocity = 0.0;
    for (int i = 0; i < 10; i++)
    {
        sum += verticalVelocityBuffer[i];
    }
    averageVerticalVelocity = sum / 10.0;
	if(averageVerticalVelocity < 10){
		count++; 
	}
	else{
		count = 0; 
	}

	if(count > 30){
		landed = true; 
	}

    bufferIndex = (bufferIndex + 1) % 10;

}

State *LandPrep::nextState_impl() {
	if (landed) 
	{	
		Serial.println("Entering Recovery!");
		return new Recovery(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV);
	}
	return nullptr;
}

enum StateId LandPrep::getId()
{
    return StateId::ID_LandPrep;
}
