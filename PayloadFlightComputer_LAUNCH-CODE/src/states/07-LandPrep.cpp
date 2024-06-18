#include "07-LandPrep.h"
#include "State.h"
#include "08-Recovery.h"
#include "FlightParams.hpp"

LandPrep::LandPrep(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator) : State(sensors, servos, attitudeStateEstimator) {}

void LandPrep::initialize_impl() {

}

void LandPrep::loop_impl() {

	if(currentTime < 2000){

		servos->paraServo_1->writeServo(SERVO_COUNTER_UNWIND); 
		servos->paraServo_2->writeServo(SERVO_CLOCK_UNWIND); //Check Servo values 
	}
	else{
		servos->paraServo_1->writeServo(SERVO_CENTER); 
		servos->paraServo_2->writeServo(SERVO_CENTER);  //Check Servo values
	}
	

	servos->cameraServo->writeServo(CAM_RETRACT); 

	// calculate vertical velocity
    float verticalVelocity = (telemPacket.altitude - lastAltitude) / (deltaTime / 1000.0);
    lastAltitude = telemPacket.altitude;

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

    bufferIndex = (bufferIndex + 1) % 10;

    // if the average vertical velocity is less than the expected landing velocity for 30 cycles, the rocket has landed
    landed = landedDebouncer.checkOut(abs(averageVerticalVelocity) < LANDING_VELOCITY);

}

State *LandPrep::nextState_impl() {

    #ifdef TEST_STATE_MACHINE

    if (currentTime > MAX_LANDPREP) //Stay in Pre-Launch for 5 seconds 
    {
        Serial.println("Entering Recovery!");
        return new Stowed(sensors, servos, attitudeStateEstimator);
    }

    #endif

	if (landed) 
	{	
		
		return new Recovery(sensors, servos, attitudeStateEstimator);
	}
	return nullptr;
}

enum StateId LandPrep::getId()
{
    return StateId::ID_LandPrep;
}