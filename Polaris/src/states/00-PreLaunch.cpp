#include "00-PreLaunch.h"
#include "01-Stowed.h"
#include "State.h"
#include "FlightParams.hpp"
#include "utility.hpp"

PreLaunch::PreLaunch(Sensorboard *sensorBoard, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(sensorBoard, attitudeStateEstimator, xbee, servos, openMV){}

void PreLaunch::initialize_impl() {
    #ifdef DEBUG_MODE
    Serial.println("PreLaunch Initialized");
    #endif
}

float PreLaunch::avgAccelZ()
{
    float sum = 0;
    uint8_t len = sizeof(accelReadingBuffer) / sizeof(float);

    for (uint8_t i = 0; i < len; i++)
    {
        sum += accelReadingBuffer[i];
    }

    return sum / len;
}

void PreLaunch::loop_impl() {
	//Serial.println("I am in Pre-Launch");
	
    altitudeBuff[altitudeBuffIdx++] = telemPacket.altitude;
    size_t altitudeBuffLen = sizeof(altitudeBuff) / sizeof(float);
    altitudeBuffIdx %= altitudeBuffLen;

    // Calibrate initial altitude
	// currently not referenced anywhere as of 10/4/2024
    if (initialAltitude == 0)
    {
        initialAltitude = telemPacket.altitude;
    }

    accelReadingBuffer[accelBuffIdx++] = telemPacket.accelZ;
    accelBuffIdx %= sizeof(accelReadingBuffer) / sizeof(float);
    launched = launchDebouncer.checkOut(avgAccelZ() > LAUNCH_ACCEL_THRESHOLD);
}


//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *PreLaunch::nextState_impl()
{
    
	#ifdef TEST_STATE_MACHINE
    if (currentTime > MAX_PRELAUNCH) //Stay in Pre-Launch for 5 seconds 
    {   
        Serial.println("Entering Stowed!"); 
        return new Stowed(sensors, attitudeStateEstimator, xbee, servos, openMV);
    }

    #endif 

	if (launched) 
	{
		Serial.println("Entering Stowed!"); 
		return new Stowed(sensors, attitudeStateEstimator, xbee, servos, openMV); 
	}
	return nullptr;
}

enum StateId PreLaunch::getId()
{
    return StateId::ID_PreLaunch;
}