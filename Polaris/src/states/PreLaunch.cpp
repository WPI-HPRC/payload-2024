#include "PreLaunch.h"
#include "State.h"
#include "Stowed.h"
#include "FlightParams.hpp"


PreLaunch::PreLaunch(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV) :  State(flash, stateEstimator, xbee, servos, openMV){}

void PreLaunch::initialize_impl() {
	this->stateStartTime = this->currentTime; 
}

float PreLaunch::avgAccelZ()
{
    float sum = 0;
    uint8_t len = sizeof(this->accelReadingBuffer) / sizeof(float);

    for (uint8_t i = 0; i < len; i++)
    {
        sum += this->accelReadingBuffer[i];
    }

    return sum / len;
}

void PreLaunch::loop_impl() {

	this->stateTime = this->currentTime - this->stateStartTime; 
	//Serial.println("I am in Pre-Launch");
	
    altitudeBuff[altitudeBuffIdx++] = telemPacket.altitude;
    size_t altitudeBuffLen = sizeof(altitudeBuff) / sizeof(float);
    altitudeBuffIdx %= altitudeBuffLen;

    // Calibrate initial altitude
	// currently not referenced anywhere as of 10/4/2024
    if (loopCount == 20) {
        float sum = 0;
        for (size_t i = 0; i < altitudeBuffLen; i++) {
            sum += altitudeBuff[i];
        }
        initialAltitude = sum / altitudeBuffLen;
    }

<<<<<<< Updated upstream:Polaris/src/states/PreLaunch.cpp
	if(averageVerticalAcceleration < LAUNCH_ACCEL_THRESHOLD){
		count++; 
	}
	else{
		count = 0; 
	}
=======
	launched = launchDebouncer.checkOut(abs(this->avgAccelZ()) > LAUNCH_ACCEL_THRESHOLD);
>>>>>>> Stashed changes:Polaris/src/states/00-PreLaunch.cpp

	if (this->attitudeStateEstimator->initialized) 
    {
        this->accelReadingBuffer[this->accelBuffIdx++] = this->telemPacket.accelZ;
        this->accelBuffIdx %= sizeof(this->accelReadingBuffer) / sizeof(float);
        launched = launchDebouncer.checkOut(this->avgAccelZ() > LAUNCH_ACCEL_THRESHOLD);
    } else {
    // Intialize EKF
        // Calculate Initial Quaternion using Accel and Mag
        // Normalize Acceleration Vector
        BLA::Matrix<3> a = {telemPacket.accelX, telemPacket.accelY, telemPacket.accelZ};
        float aLen = BLA::Norm(a);
        if (aLen != 0) {
            a /= aLen;
        }

        // Normalize Magnetometer Vector
        BLA::Matrix<3> m = {telemPacket.magX, telemPacket.magY, telemPacket.magZ};
        float mLen = BLA::Norm(m);
        if (mLen != 0) {
            m /= mLen;
        }

        // Observation Matrix

        BLA::Matrix<3> crossProd1 = Utility::crossProduct(a,m);
        BLA::Matrix<3> crossProd2 = Utility::crossProduct(crossProd1, a);
        
        BLA::Matrix<3,3> C = {
            crossProd2(0), crossProd1(0), a(0),
            crossProd2(1), crossProd1(1), a(1),
            crossProd2(3), crossProd1(2), a(2)
        };

        BLA::Matrix<4> q_0 = {
            0.5f * sqrt(C(1,1) + C(2,2) + C(3,3) + 1),
            0.5f * std::copysign(1, C(2,1) - C(1,2)) * sqrt(C(0,0) - C(1,1) - C(2,2) + 1),
            0.5f * std::copysign(1, C(0,2) - C(2,0)) * sqrt(C(1,1) - C(2,2) - C(0,0) + 1),
            0.5f * std::copysign(1, C(1,0) - C(0,1)) * sqrt(C(2,2) - C(0,0) - C(1,1) + 1)
        };

        Serial.println("<----- Initial Quaternion ----->");
        for (int i = 0; i < q_0.Rows; i++) {
            for (int j = 0; j < q_0.Cols; j++) {
                Serial.print(String(q_0(i,j)) + "\t");
            }
            Serial.println("");
        };

        this->attitudeStateEstimator->init(q_0, 0.025);
        
        Serial.println("[Prelaunch] Initialized Attitude EKF");
    }

}


//! @details If we are separating this from `Launch`, we need a time limit on this state or something
State *PreLaunch::nextState_impl()
{
	#ifdef TEST_STATE_MACHINE

    if (this->stateTime > MAX_PRELAUNCH) //Stay in Pre-Launch for 5 seconds 
    {
        Serial.println("Entering Stowed!"); 
        Stowed(this->flash, this->stateEstimator, this->xbee, this->servos, this->openMV);
    }

    #endif 

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