#include "State.h"
#include <Arduino.h>
State::State(StateEstimator *stateEstimator) : stateEstimator(stateEstimator) {}
void State::initialize() {
	this->startTime = millis();
	initialize_impl();

	 xbee->begin();

	// for z acceleration //I need to clarify why these are here 
	float transitionBufAcc[10]; 
    uint8_t transitionBufIndAcc = 0;
	
	// for vertical velocity
	int16_t transitionBufVelVert[10];
    uint8_t transitionBufIndVelVert = 0;

	// Altitude buffer
	int16_t transitionBufAlt[10];
	uint8_t transitionBufIndAlt = 0;
	int16_t altitudePreviousAvg;
}

void State::loop() {
	long long now = millis();
	this->currentTime = now - this->startTime;
	this->deltaTime = now - this->lastLoopTime;
	this->loopCount++;
	loop_impl();
	this->lastLoopTime = millis();

	//Sensor stuff here 
	this->currentState = ekf->onLoop(sensorData);
	this->telemPacket.state = this->getId();
    telemPacket.accelX = sensorData.ac_x; //Does this need to be sensorPacket? 
    telemPacket.accelY = sensorData.ac_y;
    telemPacket.accelZ = sensorData.ac_z;

    telemPacket.gyroX = sensorData.gy_x;
    telemPacket.gyroY = sensorData.gy_y;
    telemPacket.gyroZ = sensorData.gy_z;

    telemPacket.magX = sensorData.mag_x;
    telemPacket.magY = sensorData.mag_y;
    telemPacket.magZ = sensorData.mag_z;

    telemPacket.pressure = sensorData.Pressure;
    telemPacket.altitude = pressureToAltitude(sensorData.Pressure);
    telemPacket.timestamp = this->currentTime;
    telemPacket.q = currentState(0);
    telemPacket.i = currentState(1);
    telemPacket.j = currentState(2);
    telemPacket.k = currentState(3);
	telemPacket.posX = 0.0; 
	telemPacket.posY = 0.0;
	telemPacket.posZ = 0.0;
	telemPacket.velX = 0.0; 
	telemPacket.velY = 0.0;
	telemPacket.velZ = 0.0;

	telemPacket.gpsLat = sensorData.gpsLat //Make sure consistent, look at Pre-launch 
    telemPacket.gpsLong = sensorData.gpsLong
    telemPacket.gpsAltMSL = sensorData.gpsAltMSL
	telemPacket.gpsAltAGL = sensorData.gpsAltAGL
	telemPacket.epochTime = sensorData.epochTime
	telemPacket.satellites = sensorData.satellites
	telemPacket.gpsLock sensorData.gpsLock

	//Deal with these once objects are defined 
	/*uint32_t cx = 0; //Camera Centroids  
        uint32_t cy = 0;

        float targetGpsLat = 0.0f; //Target Point GPS Estimations
        float targetGpsLong = 0.0f;

        //Controls 
        uint32_t desiredServoPos1 = 0; //Servo Controls Values 
        uint32_t actualServoPos1 = 0;
        uint32_t desiredServoPos2 = 0; //Servo Controls Values 
        uint32_t actualServoPos2 = 0;
        uint32_t desiredServoPos3 = 0; //Servo Controls Values 
        uint32_t actualServoPos3 = 0;
        uint32_t desiredServoPos4 = 0; //Servo Controls Values 
        uint32_t actualServoPos4 = 0;

        float trajA = 0.0f; //Calculated Trajectory Constants 
        float trajB = 0.0f;
        float trajC = 0.0f;
        float trajD = 0.0f; */



	//Need to add in additional Payload values for sensor/telem packet 

	xbee->send(0x0013A200423F474C, &telemPacket, sizeof(telemPacket));
	flash->logData() //log data here or in States, is this also where xbee should be going and where falsh is initialized

    Serial.print("Packet Success: ");
    Serial.println(millis());

}

State *State::nextState() {
	return nextState_impl();
}


// put sensor code here
