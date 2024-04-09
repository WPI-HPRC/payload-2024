#include "LandPrep.h"
#include "State.h"
#include "Recovery.h"
#include "FlightParams.hpp"

LandPrep::LandPrep(struct Sensors *sensors, StateEstimator *stateEstimator) : State(sensors, stateEstimator) {}

void LandPrep::initialize_impl() {

}

void LandPrep::loop_impl() {

	//servos are in progress
	if(stateTime < 2000){

		this->servos->paraServo_1->writeServo(SERVO_COUNTER_UNWIND); 
		this->servos->paraServo_2->writeServo(SERVO_CLOCK_UNWIND); ; //Check Servo values 
	}
	else{
		this->servos->paraServo_1->writeServo(SERVO_CENTER); 
		this->servos->paraServo_2->writeServo(SERVO_CENTER);  //Check Servo values
	}
	

	this->servos->cameraServo->writeServo(CAM_RETRACT); 

	// calculate vertical velocity
    float verticalVelocity = (Utility::pressureToAltitude(sensorPacket.pressure) - lastAltitude) / (deltaTime / 1000.0);
    lastAltitude = Utility::pressureToAltitude(sensorPacket.pressure); 

    // add vertical velocity to cyclic buffer
    verticalVelocityBuffer[bufferIndex] = verticalVelocity;
    
    // average all values in the buffer
    float sum = 0.0;
    float averageVerticalVelocity = 0.0;
    for(int i = 0; i < 10; i++)
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
	if(landed) 
	{	
		Serial.println("Entering Recovery!");
		return new Recovery(sensors, stateEstimator);
	}
	return nullptr;
}

enum StateId LandPrep::getId()
{
    return StateId::ID_LandPrep;
}
