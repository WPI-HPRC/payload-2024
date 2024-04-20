#include "State.h"
#include <Arduino.h>
State::State() {}
void State::initialize() {
	this->startTime = millis();
	initialize_impl();
}

void State::loop() {
	long long now = millis();
	this->currentTime = now - this->startTime;
	this->deltaTime = now - this->lastLoopTime;
	this->loopCount++;
	loop_impl();
	this->lastLoopTime = millis();
	//Sensor stuff here 
	//this->currentState = stateEstimator->onLoop(sensorData); //THis is sus, check pointers and such (tomorrow)
 
    
	this->telemPacket.state = this->getId();
    telemPacket.accelX = sensorData.ac_x; 
    telemPacket.accelY = sensorData.ac_y;
    telemPacket.accelZ = sensorData.ac_z;

    telemPacket.gyroX = sensorData.gy_x;
    telemPacket.gyroY = sensorData.gy_y;
    telemPacket.gyroZ = sensorData.gy_z;

    telemPacket.magX = sensorData.mag_x;
    telemPacket.magY = sensorData.mag_y;
    telemPacket.magZ = sensorData.mag_z;

    telemPacket.pressure = sensorData.Pressure;
    telemPacket.altitude = Utility::pressureToAltitude(sensorData.Pressure);
    telemPacket.timestamp = this->currentTime;

	Utility::logData(flash, telemPacket); 
    

    //Serial.print("Packet Success: ");
    //Serial.println(millis());

}

State *State::nextState() {
	return nextState_impl();
}


