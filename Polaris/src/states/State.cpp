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
    telemPacket.altitude = pressureToAltitude(sensorData.Pressure);
    telemPacket.timestamp = this->currentTime;
    telemPacket.q = currentState(0);
    telemPacket.i = currentState(1);
    telemPacket.j = currentState(2);
    telemPacket.k = currentState(3);

	//Need to add in additional Payload values for sensor/telem packet 

	xbee->send(0x0013A200423F474C, &telemPacket, sizeof(telemPacket));

    Serial.print("Packet Success: ");
    Serial.println(millis());

}

State *State::nextState() {
	return nextState_impl();
}


// put sensor code here
